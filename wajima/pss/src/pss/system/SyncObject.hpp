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
		*	�����I�u�W�F�N�g�B
		*	�X���b�h�Ԃł̓������Ƃ邽�߂̃I�u�W�F�N�g�ł���B
		*	������r�����s�������I�u�W�F�N�g�͂��̃I�u�W�F�N�g��h��������΂��悢�B
		*/
		class SyncObject : public ObjectLevelCountedLockable<SyncObject> {
			class WaitThreads : public ObjectLevelCountedLockable<WaitThreads> {
				Win32Event	waitSync_;						//	wait�p����
				::std::vector<Thread*>	waitThreads_;	//	wait����thread�ւ̃|�C���^
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
			* ��̑ҋ@�ւ̒ʒm�B
			* �ҋ@�X���b�h�̂����A�ǂꂩ��̑ҋ@����������B
			*/
			virtual void notify();
			/**
			* ���ׂĂ̑ҋ@�ւ̒ʒm�B
			* ���ׂĂ̑ҋ@����������B
			*/
			virtual void notifyAll();
			/**
			* �ҋ@
			* �ʒm�����܂ŁA�ҋ@����B
			* wait����Lock(*this)�I�u�W�F�N�g�ɂ�郍�b�N�͉��������B
			*/
			virtual void wait();
			/**
			* ���Ԑ����t���ҋ@�B
			* �ʒm�����܂ŁA�ҋ@����B������millisecond[ms]�Œʒm����Ȃ��Ă��ҋ@�𔲂���B
			* �ҋ@����lock�ɂ���ă��b�N���ꂽ���b�N�͉��������B
			* \param millisecond millisecond[ms]�����Ēʒm����Ȃ���΁A�ҋ@�𔲂���B
			* \retval true �ʒm���ꂽ�B
			* \retval false �^�C���A�E�g�����B
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
				// unlock(monitorLock)�ɂ���āA���̃X���b�h��monitorLock->notify()�����s�ł���悤�ɂ���B
				// �������AmonitorLock->notify()���ł�waitThreads.notify()���Ă�ł���B
				// ���������Ă��̐�Aunlock(*this)���s����܂Ŏ��ۂ�notify�͎��s����Ȃ��B
				SyncObject::Unlock unlock(monitorLock);
				{
					waitThreads_.push_back( Thread::getCurrentThread() );
					while( waitThreads_.end() != ::std::find( waitThreads_.begin() , waitThreads_.end() , Thread::getCurrentThread() ) ){
						Unlock unlock(*this);
						// ���ۂɂ�millisecond�͎��Ԃ��o�߂��邱�Ƃɂ���ĕω�����ׂ������A
						// �����ł͎��s�R�X�g���l���āA�����̃R�[�h�͒ǉ����Ȃ��B
						// notify���p�ɂɂ����Ȃ���R�[�h�ł͍ň��A��������wait���邱�ƂɂȂ�B
						// �������A���̂悤�Ȋm���͒Ⴂ�Ǝv����̂ŁA�����ł͂��̂悤�Ɏ�������B
						if( !waitSync_.wait( millisecond ) ){
							return false;
						}
					}
					// lock(*this)�ɂ���āA�J�����g�X���b�h�ȊO��reset��set���ł��Ȃ��B
					// ���������āA�m����1��notify��1��wait����������B
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