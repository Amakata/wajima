#ifndef __THREADTEST_H__
#define __THREADTEST_H__

#include "system/Thread.h"
#include "system/SyncObject.h"
#include <windows.h>

class TestRunnable : public zefiro_system::Runnable
{
public:
	TestRunnable( HWND hWnd );
	virtual ~TestRunnable();
	virtual void notify();
	virtual void notifyAll();
	virtual void run();
protected:
	zefiro_system::SyncObject *syncObject_;
	HWND hWnd_;
};

class ThreadTest{
public:
	static void create( HWND hWnd );
	static void start();
	static void notify();
	static bool active__;	//	�X���b�h�����������H
	static int count__;		//	notify�����񔭓��������H
	static TestRunnable *r__;
	static zefiro_system::Thread *thread__;
};



#endif //__THREADTEST_H__