/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/system/SyncObject.h,v 1.2 2002/11/04 16:29:19 ama Exp $
 */

#ifndef __SYNCOBJECT_H__
#define __SYNCOBJECT_H__

#include <vector>
#include <string>

#include "Mutex.h"
#include "sys/Win32Event.h"
#include "Thread.h"

namespace zefiro_system {
	/**
	 *	�����I�u�W�F�N�g�B
	 *	�X���b�h�Ԃł̓������Ƃ邽�߂̃I�u�W�F�N�g�ł���B
	 *	������r�����s�������I�u�W�F�N�g�͂��̃I�u�W�F�N�g��h��������΂��悢�B
	 */
	class SyncObject {
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
		 * wait����lock���\�b�h�ɂ���ă��b�N���ꂽ���b�N�͉��������B
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
		/**
		 * ���b�N����B
		 * �����X���b�h�ōċA�I�Ƀ��b�N��
		 */
		virtual void lock();
		/**
		 * �A�����b�N����B
		 */
		virtual void unlock();
		virtual std::string toString() const;
	protected:
		SyncObject( const SyncObject &syncObject );
		SyncObject &operator =( const SyncObject &syncObject );
		bool doWait( int millisecond = INFINITE );
		Mutex *monitorMutex_;					//	���j�^�[�p�r��
		Win32Event	*monitorSync_;				//	���j�^�[�p����
		int	monitorOwnerID_;					//	���j�^�[�̏��LThread��ID
		int countOfMonitorLock_;				//	���j�^�[���b�N���ꂽ��
		int countOfMonitorLockWait_;			//	���j�^�[���b�N��҂��Ă���X���b�h�̐�
		Mutex *waitMutex_;				//	wait�p�r��
		Win32Event	*waitSync_;						//	wait�p����
		std::vector<Thread*>	waitThreads_;	//	wait����thread�ւ̃|�C���^
	};
};

#endif //__SYNCOBJECT_H__