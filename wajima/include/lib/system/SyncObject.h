/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/include/lib/system/Attic/SyncObject.h,v 1.1 2002/05/26 17:10:36 ama Exp $
 */

#ifndef __SYNCOBJECT_H__
#define __SYNCOBJECT_H__

#include <vector>
#include <string>

#include "system/Mutex.h"
#include "system/sys/Win32Event.h"
#include "system/Thread.h"

namespace zefiro_system {
	class SyncObject {
	public:
		SyncObject();
		virtual ~SyncObject();
		virtual void notify();
		virtual void notifyAll();
		virtual void wait();
		virtual bool wait( int millisecond );
		virtual void lock();
		virtual void unlock();
		virtual std::string toString() const;
	protected:
		SyncObject( const SyncObject &syncObject );
		SyncObject &operator =( const SyncObject &syncObject );
		Mutex *syncObjectMutex_;
		std::vector<Thread*>	waitThreads_;	//	waitíÜÇÃthreadÇ÷ÇÃÉ|ÉCÉìÉ^
		Win32Event	*sync_;						//	ìØä˙
		int	countOfHasNotified_;				//	notifyÇ≥ÇÍÇΩâÒêî
	};
};

#endif //__SYNCOBJECT_H__