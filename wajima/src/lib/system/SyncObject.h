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
	 *	同期オブジェクト。
	 *	スレッド間での同期をとるためのオブジェクトである。
	 *	同期や排他を行いたいオブジェクトはこのオブジェクトを派生させればいよい。
	 */
	class SyncObject {
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
		 * wait中はlockメソッドによってロックされたロックは解除される。
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
		/**
		 * ロックする。
		 * 同じスレッドで再帰的にロックを
		 */
		virtual void lock();
		/**
		 * アンロックする。
		 */
		virtual void unlock();
		virtual std::string toString() const;
	protected:
		SyncObject( const SyncObject &syncObject );
		SyncObject &operator =( const SyncObject &syncObject );
		bool doWait( int millisecond = INFINITE );
		Mutex *monitorMutex_;					//	モニター用排他
		Win32Event	*monitorSync_;				//	モニター用同期
		int	monitorOwnerID_;					//	モニターの所有ThreadのID
		int countOfMonitorLock_;				//	モニターロックされた回数
		int countOfMonitorLockWait_;			//	モニターロックを待っているスレッドの数
		Mutex *waitMutex_;				//	wait用排他
		Win32Event	*waitSync_;						//	wait用同期
		std::vector<Thread*>	waitThreads_;	//	wait中のthreadへのポインタ
	};
};

#endif //__SYNCOBJECT_H__