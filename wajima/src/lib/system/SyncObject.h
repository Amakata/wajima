/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/system/SyncObject.h,v 1.3 2002/11/06 18:42:54 ama Exp $
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
	 *	�����I�u�W�F�N�g�B
	 *	�X���b�h�Ԃł̓������Ƃ邽�߂̃I�u�W�F�N�g�ł���B
	 *	������r�����s�������I�u�W�F�N�g�͂��̃I�u�W�F�N�g��h��������΂��悢�B
	 */
	class SyncObject : public ObjectLevelCountedLockable<SyncObject> {
		class WaitThreads : public ObjectLevelCountedLockable<WaitThreads> {
			Win32Event	waitSync_;						//	wait�p����
			std::vector<Thread*>	waitThreads_;	//	wait����thread�ւ̃|�C���^
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
			bool doWait( int millisecond = INFINITE ){
				waitThreads_.push_back( Thread::getCurrentThread() );
				while( waitThreads_.end() != std::find( waitThreads_.begin() , waitThreads_.end() , Thread::getCurrentThread() ) ){
					Unlock unlock(*this);
					if( !waitSync_.wait( millisecond ) ){
						return false;
					}
				}
				waitSync_.reset();
				return true;
			}
		};
		WaitThreads waitThreads_;
	public:
		SyncObject():
			waitThreads_(),
			monitorSync_(new Win32Event()),monitorOwnerID_(Thread::NULLTHREAD){
			ZEFIRO_LOG( "NORMAL" , "SyncObject::SyncObject()" + toString());
			monitorSync_->reset();
		}
		virtual ~SyncObject(){
			ZEFIRO_LOG( "NORMAL" , "SyncObject::~SyncObject()" + toString());
			delete monitorSync_;
		}
		/**
		 * ��̑ҋ@�ւ̒ʒm�B
		 * �ҋ@�X���b�h�̂����A�ǂꂩ��̑ҋ@����������B
		 */
		virtual void notify(){
			ZEFIRO_LOG( "NORMAL" , "SyncObject::notify() Begin" + toString());
			waitThreads_.notify();
			ZEFIRO_LOG( "NORMAL" , "SyncObject::notify() End" + toString());
		}
		/**
		 * ���ׂĂ̑ҋ@�ւ̒ʒm�B
		 * ���ׂĂ̑ҋ@����������B
		 */
		virtual void notifyAll(){
			ZEFIRO_LOG( "NORMAL" , "SyncObject::notifyAll() Begin" + toString());
			waitThreads_.notifyAll();
			ZEFIRO_LOG( "NORMAL" , "SyncObject::notifyAll() End" + toString());
		}
		/**
		 * �ҋ@
		 * �ʒm�����܂ŁA�ҋ@����B
		 * wait����lock���\�b�h�ɂ���ă��b�N���ꂽ���b�N�͉��������B
		 */
		virtual void wait(){
			ZEFIRO_LOG( "NORMAL" , "SyncObject::wait() Begin" + toString());
			WaitThreads::Lock lock(waitThreads_);
			{
				Lock unlock(*this);	
				waitThreads_.doWait();
			}
			ZEFIRO_LOG( "NORMAL" , "SyncObject::wait() End" + toString());
		}
		/**
		 * ���Ԑ����t���ҋ@�B
		 * �ʒm�����܂ŁA�ҋ@����B������millisecond[ms]�Œʒm����Ȃ��Ă��ҋ@�𔲂���B
		 * �ҋ@����lock�ɂ���ă��b�N���ꂽ���b�N�͉��������B
		 * \param millisecond millisecond[ms]�����Ēʒm����Ȃ���΁A�ҋ@�𔲂���B
		 * \retval true �ʒm���ꂽ�B
		 * \retval false �^�C���A�E�g�����B
		 */
		virtual bool wait( int millisecond ){
			bool result;
			ZEFIRO_LOG( "NORMAL" , "SyncObject::wait( int ) Begin" + toString());
			WaitThreads::Lock lock(waitThreads_);
			{
				Unlock unlock(*this);
				result = waitThreads_.doWait( millisecond );
			}
			ZEFIRO_LOG( "NORMAL" , "SyncObject::wait( int ) End" + toString());
			return result;
		}
		virtual std::string toString() const{
			std::ostringstream ostrstr;	
			ostrstr << 
						"( monitor owner id = " << monitorOwnerID_ << 
						" , monitor sync = "  << monitorSync_->toString() <<  " ) ";

			return ostrstr.str();
		}
	protected:
		SyncObject( const SyncObject &syncObject );
		SyncObject &operator =( const SyncObject &syncObject );
		Win32Event	*monitorSync_;				//	���j�^�[�p����
		int	monitorOwnerID_;					//	���j�^�[�̏��LThread��ID
	};
};

#endif //__SYNCOBJECT_H__