#ifndef __MUTEX_H__
#define __MUTEX_H__

/**
 * $ Header: $
 */

#include <windows.h>

namespace zefiro_thread {
	class Mutex
	{
	public:
		Mutex();
		virtual ~Mutex();
		void lock();
		void unlock();
	private:
		CRITICAL_SECTION _criticalSection;
	};
};
#endif //__MUTEX_H__