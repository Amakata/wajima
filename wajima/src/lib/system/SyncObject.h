/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/system/SyncObject.h,v 1.4 2002/11/07 10:38:40 ama Exp $
 */

#ifndef __SYNCOBJECT_H__
#define __SYNCOBJECT_H__

#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

#include "std/Logger.h"
#include "std/Assert.h"
#include "Mutex.h"
#include "sys/Win32Event.h"
#include "Thread.h"
#include "ThreadingModel.h"

namespace zefiro_system {
	/**
	 *	同期オブジェクト。
	 *	スレッド間での同期をとるためのオブジェクトである。
	 *	同期や排他を行いたいオブジェクトはこのオブジェクトを派生させればいよい。
	 */
	class SyncObject : public ObjectLevelCountedLockable<SyncObject> {
		class WaitThreads : public ObjectLevelCountedLockable<WaitThreads> {
			Win32Event	waitSync_;						//	wait用同期
			std::vector<Thread*>	waitThreads_;	//	wait中のthreadへのポインタ
		public:
			WaitThreads(){
				waitSync_.reset();
			}
			virtual ~WaitThreads(){
			}
			void notify(){
				Lock lock(*this);
				{
					if( waitThreads_.size() > 0 ){
						waitThreads_.erase( waitThreads_.begin() );
						waitSync_.set();
					}
				}
			}
			void notifyAll(){
				Lock lock(*this);
				{
					if( waitThreads_.size() > 0 ){
						waitThreads_.erase( waitThreads_.begin() , waitThreads_.end() );
						waitSync_.set();
					}
				}
			}
			bool wait( SyncObject &monitorLock , int millisecond = INFINITE ){
				Lock lock(*this);
				{
					SyncObject::Unlock unlock(monitorLock);
					{
						waitThreads_.push_back( Thread::getCurrentThread() );
						while( waitThreads_.end() != std::find( waitThreads_.begin() , waitThreads_.end() , Thread::getCurrentThread() ) ){
							Unlock unlock(*this);
							if( !waitSync_.wait( millisecond ) ){
								return false;
							}
						}
						waitSync_.reset();
					}
				}
				return true;
			}
		};
		WaitThreads waitThreads_;
	public:
		SyncObject(): waitThreads_(){
			ZEFIRO_LOG( "NORMAL" , "SyncObject::SyncObject()" + toString());
		}
		virtual ~SyncObject(){
			ZEFIRO_LOG( "NORMAL" , "SyncObject::~SyncObject()" + toString());
		}
		/**
		 * 一つの待機への通知。
		 * 待機スレッドのうち、どれか一つの待機を解除する。
		 */
		virtual void notify(){
			ZEFIRO_LOG( "NORMAL" , "SyncObject::notify() Begin" + toString());
			waitThreads_.notify();
			ZEFIRO_LOG( "NORMAL" , "SyncObject::notify() End" + toString());
		}
		/**
		 * すべての待機への通知。
		 * すべての待機を解除する。
		 */
		virtual void notifyAll(){
			ZEFIRO_LOG( "NORMAL" , "SyncObject::notifyAll() Begin" + toString());
			waitThreads_.notifyAll();
			ZEFIRO_LOG( "NORMAL" , "SyncObject::notifyAll() End" + toString());
		}
		/**
		 * 待機
		 * 通知されるまで、待機する。
		 * wait中はlockメソッドによってロックされたロックは解除される。
		 */
		virtual void wait(){
			ZEFIRO_LOG( "NORMAL" , "SyncObject::wait() Begin" + toString());
			waitThreads_.wait( *this );
			ZEFIRO_LOG( "NORMAL" , "SyncObject::wait() End" + toString());
		}
		/**
		 * 時間制限付き待機。
		 * 通知されるまで、待機する。ただしmillisecond[ms]で通知されなくても待機を抜ける。
		 * 待機中はlockによってロックされたロックは解除される。
		 * \param millisecond millisecond[ms]たって通知されなければ、待機を抜ける。
		 * \retval true 通知された。
		 * \retval false タイムアウトした。
		 */
		virtual bool wait( int millisecond ){
			ZEFIRO_LOG( "NORMAL" , "SyncObject::wait( int ) Begin" + toString());
			bool result = waitThreads_.wait( *this , millisecond );
			ZEFIRO_LOG( "NORMAL" , "SyncObject::wait( int ) End" + toString());
			return result;
		}
		virtual std::string toString() const{
			return std::string();
		}
	protected:
		SyncObject( const SyncObject &syncObject );
		SyncObject &operator =( const SyncObject &syncObject );
	};
};

#endif //__SYNCOBJECT_H__