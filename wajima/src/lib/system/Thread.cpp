/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/system/Thread.cpp,v 1.8 2002/11/07 10:38:44 ama Exp $
 */

#include "Thread.h"
#include "std/Logger.h"
#include "std/Assert.h"

#include <process.h>
#include <sstream>

namespace zefiro_system {
	const int Thread::NULLTHREAD = -1;
	
	Thread::Thread( int stackSize )
		:runnable_(NULL),thread_(NULL),threadID_(0),constructError_(0),hasStarted_(false),joinable_(true),canRemoveRunnable_(true),name_(""){
		create( stackSize );
	}
	Thread::Thread( std::string name , int stackSize )
		:runnable_(NULL),thread_(NULL),threadID_(0),constructError_(0),hasStarted_(false),joinable_(true),canRemoveRunnable_(true),name_(name){
		create( stackSize );
	}
	Thread::Thread( Runnable *r , int stackSize )
		:runnable_(r),thread_(NULL),threadID_(0),constructError_(0),hasStarted_(false),joinable_(true),canRemoveRunnable_(true),name_(""){
		create( stackSize );
	}
	Thread::Thread( Runnable *r , std::string name , int stackSize )
		:runnable_(r),thread_(NULL),threadID_(0),constructError_(0),hasStarted_(false),joinable_(true),canRemoveRunnable_(true),name_(name){
		create( stackSize );
	}

	bool Thread::isAvailable(){
		Lock lock(*this);
		ZEFIRO_LOG( "NORMAL" , "Thread::isAvailable()" + toString());
		return thread_ != NULL;
	}
	bool Thread::isJoinable(){
		Lock lock(*this);
		ZEFIRO_LOG( "NORMAL" , "Thread::isJoinable()" + toString());
		return joinable_;
	}
	void Thread::setJoinable( bool joinable ){
		Lock lock(*this);
		ZEFIRO_LOG( "NORMAL" , "Thread::setJoinable()" + toString());
	}
	bool Thread::canRemoveRunnable(){
		Lock lock(*this);
		return canRemoveRunnable_;
	}
	void Thread::setCanRemoveRunnable( bool canRemoveRunnable ){
		Lock lock(*this);
		bool canRemoveRunnable_ = canRemoveRunnable;
	}
	void Thread::start(){
		Lock lock(*this);
		ZEFIRO_LOG( "NORMAL" , "Thread::start() Begin" + toString());
		if( !isAvailable() ){
			ZEFIRO_LOG( "ERROR" , "Thread::start()" + toString());
			WIN32ASSERT( constructError_ );
		}
		if( !hasStarted_ ){
			hasStarted_ = true;
		}else{
			throw IllegalThreadStateException();
		}
		if( -1 == ResumeThread( thread_ ) ){
			ZEFIRO_LOG( "ERROR" , "Thread::start()" + toString());
			DWORD error = GetLastError();
			WIN32ASSERT( error );
		}
		ZEFIRO_LOG( "NORMAL" , "Thread::start() End" + toString());
	}
	int Thread::getThreadID(){
		Lock lock(*this);
		return threadID_;
	}
	std::string Thread::getName(){
		Lock lock(*this);
		return name_;
	}
	int Thread::getPriority(){
		Lock lock(*this);
		int result;
		if( THREAD_PRIORITY_ERROR_RETURN == ( result = GetThreadPriority( thread_ ) ) ){
			WIN32ASSERT( GetLastError() );
		}
		return result;
	}
	void Thread::setPriority( int priority ){
		ZEFIRO_STD_ASSERT( priority >= 0 );
		Lock lock(*this);
		if( 0 == SetThreadPriority( thread_ , priority ) ){
			WIN32ASSERT( GetLastError() );
		}
	}
	int Thread::join(){
		return doJoin( 0 );
	}
	int Thread::join( int millisecond ){

		return doJoin( millisecond );
	}
	void Thread::yield(){
		ZEFIRO_LOG( "NORMAL" , "Thread::yield() Begin");
		Sleep(0);
		ZEFIRO_LOG( "NORMAL" , "Thread::yield() End");
	}
	void Thread::sleep( int millisecond ){
		ZEFIRO_LOG( "NORMAL" , "Thread::sleep() Begin");
		ZEFIRO_STD_ASSERT( millisecond >= 0 );
		Sleep(millisecond);
		ZEFIRO_LOG( "NORMAL" , "Thread::sleep() End");
	}
	void Thread::exit( int exitCode ){
		bool joinable;
		ZEFIRO_LOG( "NORMAL" , "Thread::exit() Begin");
		Thread *currentThread = getCurrentThread();
		{
			Thread::Lock lock(*currentThread);
			joinable = currentThread->joinable_;
			if( ! joinable ){
				if( currentThread->canRemoveRunnable_ ){
					delete currentThread->runnable_;
				}
			}
		}
		if( !joinable){
			delete currentThread;
		}
		ZEFIRO_LOG( "NORMAL" , "Thread::exit() End");
		_endthreadex( exitCode );
	}
	int Thread::getCurrentThreadID(){
		return GetCurrentThreadId();
	}
	Thread* Thread::getCurrentThread(){
		ZEFIRO_LOG( "NORMAL" , "Thread::getCurrentThread() Begin" );
		threadsMutex__.lock();
		if( threads__.size() == 0 ){
			addMainThread();
		}
		std::vector<Thread*>::iterator itr;
		Thread *result;
		if( threads__.end() != (itr = getCurrentThreadIterator() ) ){
			result = (*itr);
		}else{
			result = NULL;
		}
		threadsMutex__.unlock();
		ZEFIRO_LOG( "NORMAL" , "Thread::getCurrentThread() End" );
		return result;
	}
	void Thread::run(){
		ZEFIRO_LOG( "NORMAL" , "Thread::run()" + toString());
	}
	std::string Thread::toString() const{
		std::ostringstream	ostrstr;
		ostrstr << " Thread HANDLE = " << thread_ << " , Thread ID = " << threadID_ << " , hasStarted = " << hasStarted_ << " , joinable = " << joinable_ << " , name = " << name_ << " , canRemoveRunnable = " << canRemoveRunnable_ << " , constructError = " << constructError_; 		
		return ostrstr.str();
	}
	void Thread::create( int stackSize ){
		ZEFIRO_STD_ASSERT( stackSize >= 0 );
		threadsMutex__.lock();					//	デッドロックを避けるために必ずこの順番でロック
		if( threads__.size() == 0 ){
			addMainThread();
		}
		{
			Lock lock(*this);
			ZEFIRO_LOG( "NORMAL" , "Thread::Thread( Runnable *, int ) Begin" + toString());
			if( NULL == (thread_ = (HANDLE)_beginthreadex( NULL , stackSize , (unsigned (__stdcall *)(void *))runProc , this , CREATE_SUSPENDED , &threadID_ ) ) ){
				constructError_ = GetLastError();	//	コンストラクタ内で例外は発生させたくないので、エラーを記憶
			}
			threads__.push_back( this );
			ZEFIRO_LOG( "NORMAL" , "Thread::Thread( Runnable *, int ) END" + toString() );
		}
		threadsMutex__.unlock();
	}
	int Thread::doJoin( int millisecond ){
		ZEFIRO_STD_ASSERT( millisecond >= 0 );
		DWORD exitCode;
		{
			Lock lock(*this);
			ZEFIRO_LOG( "NORMAL" , "Thread::join() Begin" + toString());
			if( !isAvailable() ){
				ZEFIRO_LOG( "ERROR" , "Thread::join()" + toString());
				WIN32ASSERT( constructError_ );
			}
		}
		DWORD result = WaitForSingleObject( thread_ , millisecond );
		{
			Lock lock(*this);
			switch( result ){
			case WAIT_ABANDONED:
			case WAIT_OBJECT_0:
				break;
			case WAIT_TIMEOUT:
				ZEFIRO_LOG( "NORMAL" , "Thread::join() End" + toString());
				throw TimeOutException();
			case WAIT_FAILED:
				ZEFIRO_LOG( "ERROR" , "Thread::join()" + toString());
				WIN32ASSERT( GetLastError() );
			}
			if( 0 == GetExitCodeThread( thread_ , &exitCode ) ){
				ZEFIRO_LOG( "ERROR" , "Thread::join()" + toString());
				WIN32ASSERT( GetLastError() );
			}
		}
		ZEFIRO_LOG( "NORMAL" , "Thread::join() End" + toString());
		delete this;
		return exitCode;
	}
	void Thread::addMainThread(){
		ZEFIRO_LOG( "NORMAL" , "Thread::addMainThread() Begin");
		Thread *mainThread = new Thread( GetCurrentThread() , GetCurrentThreadId() );
		threadsMutex__.lock();
		threads__.push_back( mainThread );
		threadsMutex__.unlock();
		ZEFIRO_LOG( "NORMAL" , "Thread::addMainThread() End");
	}
	Thread::Thread( HANDLE thread , unsigned int threadid )
		:thread_(thread),threadID_(threadid),
		runnable_(false),constructError_(0),
		hasStarted_(true),
		joinable_(false),canRemoveRunnable_(false),name_("main"){
		ZEFIRO_LOG( "NORMAL" , "Thread::Thread( HANDLE , unsigned int )" + toString());
	}
	Thread::~Thread(){
		ZEFIRO_LOG( "NORMAL" , "Thread::~Thread() Begin" + toString());
		threadsMutex__.lock();
		removeThread( this );
		threadsMutex__.unlock();
		if( isAvailable() ){
			CloseHandle( thread_ );
		}
		ZEFIRO_LOG( "NORMAL" , "Thread::~Thread() End" + toString());
	}
	int Thread::runProc( Thread *thread ){
		ZEFIRO_LOG( "NORMAL" , "Thread::runProc( Thread * ) Begin" + thread->toString() );
		if( thread->runnable_ == NULL ){
			thread->run();
		}else{
			thread->runnable_->run();
		}
		Thread::exit(0);
		ZEFIRO_LOG( "NORMAL" , "Thread::runProc( Thread * ) End" + thread->toString());
		return 0;
	}
	std::vector<Thread*>::iterator Thread::getCurrentThreadIterator(){
		int currentID = getCurrentThreadID();
		std::vector<Thread*>::iterator end = threads__.end();
		for( std::vector<Thread*>::iterator itr = threads__.begin() ; itr != end ; ++itr ){
			if(  (*itr)->getThreadID() == currentID ){
				return itr;
			}
		}
		return end;
	}
	void Thread::removeThread( Thread *thread ){
		std::vector<Thread*>::iterator end = threads__.end();
		for( std::vector<Thread*>::iterator itr = threads__.begin() ; itr != end ; ++itr ){
			if( *itr == thread ){
				threads__.erase( itr );
				return;
			}
		}
	}

};