/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/include/lib/system/Attic/Mutex.h,v 1.3 2002/05/25 15:58:21 ama Exp $
 */

#ifndef __MUTEX_H__
#define __MUTEX_H__


#include <windows.h>
#include <string>

namespace zefiro_system {
	class Mutex
	{
	public:
		Mutex();
		virtual ~Mutex();
		void lock();
		void unlock();
		virtual std::string toString() const;
	private:
		CRITICAL_SECTION criticalSection_;
	};
};
#endif //__MUTEX_H__