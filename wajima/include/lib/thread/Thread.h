#ifndef __THREAD_H__
#define __THREAD_H__
/**
 * $ Header: $
 */

#include <windows.h>
#include <string>
#include "thread/Runnable.h"
#include "thread/Mutex.h"
#include "thread/IllegalThreadStateException.h"
#include <std/sys/Win32Assert.h>

namespace zefiro_thread {
	class Thread : public Runnable
	{
	public:
		Thread( int stackSize = 0 );
		Thread( std::string name , int stackSize = 0 );
		Thread( Runnable *runnable , int stackSize = 0 );
		Thread( Runnable *runnable , std::string name , int stackSize = 0 );
		bool isAvailable() const;
		void start();
		virtual void run();
	protected:
		virtual ~Thread();
		static int runProc( Thread *thread );
		HANDLE	_thread;
		DWORD	_threadID;
		Runnable *_runnable;
		DWORD	_constructError;
		Mutex	*_mutex;
		bool	_start;
	};
};


#endif //__THREAD_H__