#ifndef __MUTEX_H__
#define __MUTEX_H__


#include <windows.h>
#include <string>
#include <sstream>

namespace zefiro {
	namespace system {
		class Mutex
		{
		public:
			Mutex() {
				InitializeCriticalSection( &criticalSection_ );
			}
			virtual ~Mutex() {
				DeleteCriticalSection( &criticalSection_ );
			}
			void lock() {
				EnterCriticalSection( &criticalSection_ );
			}
			void unlock() {
				LeaveCriticalSection( &criticalSection_ );
			}
			virtual ::std::string toString() const {
				::std::ostringstream ostrstr;
				ostrstr << " Mutex Pointer = " << this;
				return ostrstr.str();
			}
		private:
			CRITICAL_SECTION criticalSection_;
		};
	}
}

#endif //__MUTEX_H__