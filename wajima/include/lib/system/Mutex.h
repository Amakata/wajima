#ifndef __MUTEX_H__
#define __MUTEX_H__

/**
 * $ Header: $
 */

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