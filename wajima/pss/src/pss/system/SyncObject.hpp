#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

#include "Mutex.hpp"
#include "Win32Event.hpp"
#include "Thread.hpp"
#include "ThreadingModel.hpp"

namespace pss {
	namespace system {
		/**
		*	同期オブジェクト。
		*	スレッド間での同期をとるためのオブジェクトである。
		*	同期や排他を行いたいオブジェクトはこのオブジェクトを派生させればいよい。
		*/
		class SyncObject : public ObjectLevelCountedLockable<SyncObject> {
			class WaitThreads : public ObjectLevelCountedLockable<WaitThreads> {
				Win32Event	waitSync_;						//	wait用同期
				::std::vector<Thread*>	waitThreads_;	//	wait中のthreadへのポインタ
			public:
				WaitThreads();
				virtual ~WaitThreads();
				void notify();
				void notifyAll();
				bool wait( SyncObject &monitorLock , int millisecond = INFINITE );
			};
			WaitThreads waitThreads_;
		public:
			SyncObject();
			virtual ~SyncObject();
			/**
			* 一つの待機への通知。
			* 待機スレッドのうち、どれか一つの待機を解除する。
			*/
			virtual void notify();
			/**
			* すべての待機への通知。
			* すべての待機を解除する。
			*/
			virtual void notifyAll();
			/**
			* 待機
			* 通知されるまで、待機する。
			* wait中はLock(*this)オブジェクトによるロックは解除される。
			*/
			virtual void wait();
			/**
			* 時間制限付き待機。
			* 通知されるまで、待機する。ただしmillisecond[ms]で通知されなくても待機を抜ける。
			* 待機中はlockによってロックされたロックは解除される。
			* \param millisecond millisecond[ms]たって通知されなければ、待機を抜ける。
			* \retval true 通知された。
			* \retval false タイムアウトした。
			*/
			virtual bool wait( int millisecond );
			virtual ::std::string toString() const;
		protected:
			SyncObject( const SyncObject &syncObject );
			SyncObject &operator =( const SyncObject &syncObject );
		};
	}
}

#ifdef PSS_SYSTEM_SYNCOBJECT_COMPILE
namespace pss {
	namespace system {
		SyncObject::WaitThreads::WaitThreads(){
			waitSync_.reset();
		}
		SyncObject::WaitThreads::~WaitThreads(){
		}
		void SyncObject::WaitThreads::notify(){
			Lock lock(*this);
			{
				if( waitThreads_.size() > 0 ){
					waitThreads_.erase( waitThreads_.begin() );
					waitSync_.set();
				}
			}
		}
		void SyncObject::WaitThreads::notifyAll(){
			Lock lock(*this);
			{
				if( waitThreads_.size() > 0 ){
					waitThreads_.erase( waitThreads_.begin() , waitThreads_.end() );
					waitSync_.set();
				}
			}
		}
		bool SyncObject::WaitThreads::wait( SyncObject &monitorLock , int millisecond ){
			Lock lock(*this);
			{
				// unlock(monitorLock)によって、他のスレッドがmonitorLock->notify()を実行できるようにする。
				// ただし、monitorLock->notify()内ではwaitThreads.notify()を呼んでいる。
				// したがってこの先、unlock(*this)が行われるまで実際にnotifyは実行されない。
				SyncObject::Unlock unlock(monitorLock);
				{
					waitThreads_.push_back( Thread::getCurrentThread() );
					while( waitThreads_.end() != ::std::find( waitThreads_.begin() , waitThreads_.end() , Thread::getCurrentThread() ) ){
						Unlock unlock(*this);
						// 実際にはmillisecondは時間が経過することによって変化するべきだが、
						// ここでは実行コストを考えて、それらのコードは追加しない。
						// notifyが頻繁におこなわれるコードでは最悪、無限時間waitすることになる。
						// しかし、そのような確率は低いと思われるので、ここではこのように実装する。
						if( !waitSync_.wait( millisecond ) ){
							return false;
						}
					}
					// lock(*this)によって、カレントスレッド以外はresetもsetもできない。
					// したがって、確実に1つのnotifyが1つのwaitを解除する。
					waitSync_.reset();
				}
			}
			return true;
		}

		SyncObject::SyncObject(): waitThreads_(){
		}
		SyncObject::~SyncObject(){
		}
		void SyncObject::notify(){
			waitThreads_.notify();
		}
		void SyncObject::notifyAll(){
			waitThreads_.notifyAll();
		}
		void SyncObject::wait(){
			waitThreads_.wait( *this );
		}
		bool SyncObject::wait( int millisecond ){
			bool result = waitThreads_.wait( *this , millisecond );
			return result;
		}
		::std::string SyncObject::toString() const{
			return ::std::string();
		}	
	}
}
#endif