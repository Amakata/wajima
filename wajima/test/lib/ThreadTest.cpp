#include "ThreadTest.h"

#include <sstream>
#include <windows.h>

TestRunnable::TestRunnable( HWND hWnd ):syncObject_(new zefiro_system::SyncObject()),hWnd_(hWnd){
}
TestRunnable::~TestRunnable(){
	delete syncObject_;
}
void TestRunnable::notify(){
	syncObject_->notify();
}
void TestRunnable::notifyAll(){
	syncObject_->notifyAll();
}
void TestRunnable::run(){
	zefiro_system::Thread *thread = zefiro_system::Thread::getCurrentThread();
	std::ostringstream ostrstr;
	ostrstr << thread << " " << thread->getThreadID();
	HDC hdc = GetDC( hWnd_ );
	for( int y=0 ; y<16 ; y+=16 ){
		TextOut(hdc,10,y,ostrstr.str().c_str(),(int)ostrstr.str().size());
		syncObject_->wait();
	}
	ReleaseDC( hWnd_ , hdc );
}

void ThreadTest::create( HWND hWnd ){
	if( count__ == 0 && !active__ ){
		r__ = new TestRunnable( hWnd );
		// wait()でどのスレッドも待機していないときにnotifyを実行しても問題ないか？
		r__->notifyAll();
		r__->notify();
		thread__ = new zefiro_system::Thread(r__,"TestThread");
	}
}
void ThreadTest::start(){
	if( count__ == 0 && !active__ ){
		thread__->setJoinable( false );
		thread__->start();
		active__ = true;
	}
}
void ThreadTest::notify(){
	if( !active__ ){
		return;
	}
	if( count__ < 1 ){
		r__->notify();
		++count__;
	}else{
		count__ = 0;
		active__ = false;
	}
}

TestRunnable* ThreadTest::r__;
zefiro_system::Thread* ThreadTest::thread__;
int ThreadTest::count__ = 0;
bool ThreadTest::active__ = false;