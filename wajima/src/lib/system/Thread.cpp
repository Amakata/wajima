/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/system/Thread.cpp,v 1.7 2002/11/04 16:29:19 ama Exp $
 */

#include "Thread.h"
#include "std/Logger.h"
#include "std/Assert.h"

#include <process.h>
#include <sstream>

namespace zefiro_system {
	std::vector<Thread *>	Thread::threads__;
	Mutex Thread::threadsMutex__;
	const int Thread::NULLTHREAD = -1;
	
	Thread::Thread( int stackSize )
		:runnable_(NULL),thread_(NULL),threadMutex_(new Mutex()),threadID_(0),constructError_(0),hasStarted_(false),joinable_(true),canRemoveRunnable_(true),name_(""){
		create( stackSize );
	}
	Thread::Thread( std::string name , int stackSize )
		:runnable_(NULL),thread_(NULL),threadMutex_(new Mutex()),threadID_(0),constructError_(0),hasStarted_(false),joinable_(true),canRemoveRunnable_(true),name_(name){
		create( stackSize );
	}
	Thread::Thread( Runnable *r , int stackSize )
		:runnable_(r),thread_(NULL),threadMutex_(new Mutex()),threadID_(0),constructError_(0),hasStarted_(false),joinable_(true),canRemoveRunnable_(true),name_(""){
		create( stackSize );
	}
	Thread::Thread( Runnable *r , std::string name , int stackSize )
		:runnable_(r),thread_(NULL),threadMutex_(new Mutex()),threadID_(0),constructError_(0),hasStarted_(false),joinable_(true),canRemoveRunnable_(true),name_(name){
		create( stackSize );
	}

	bool Thread::isAvailable() const {
		threadMutex_->lock();
		ZEFIRO_LOG( "NORMAL" , "Thread::isAvailable()" + toString());
		bool result = thread_ != NULL;
		threadMutex_->unlock();
		return result;
	}
	bool Thread::isJoinable() const {
		threadMutex_->lock();
		ZEFIRO_LOG( "NORMAL" , "Thread::isJoinable() Begin" + toString());
		bool result = joinable_;
		ZEFIRO_LOG( "NORMAL" , "Thread::isJoinable() End" + toString());
		threadMutex_->unlock();
		return result;
	}
	void Thread::setJoinable( bool joinable ){
		threadMutex_->lock();
		ZEFIRO_LOG( "NORMAL" , "Thread::setJoinable() Begin" + toString());
		joinable_ = joinable;
		ZEFIRO_LOG( "NORMAL" , "Thread::setJoinable() End" + toString());
		threadMutex_->unlock();
	}
	bool Thread::canRemoveRunnable() const {
		threadMutex_->lock();
		bool result = canRemoveRunnable_;
		threadMutex_->unlock();
		return result;
	}
	void Thread::setCanRemoveRunnable( bool canRemoveRunnable ){
		threadMutex_->lock();
		bool canRemoveRunnable_ = canRemoveRunnable;
		threadMutex_->unlock();
	
	}
	void Thread::start(){
		threadMutex_->lock();
		ZEFIRO_LOG( "NORMAL" , "Thread::start() Begin" + toString());
		if( !isAvailable() ){
			ZEFIRO_LOG( "ERROR" , "Thread::start()" + toString());
			threadMutex_->unlock();
			WIN32ASSERT( constructError_ );
		}
		if( !hasStarted_ ){
			hasStarted_ = true;
		}else{
			threadMutex_->unlock();
			throw IllegalThreadStateException();
		}
		if( -1 == ResumeThread( thread_ ) ){
			ZEFIRO_LOG( "ERROR" , "Thread::start()" + toString());
			DWORD error = GetLastError();
			threadMutex_->unlock();
			WIN32ASSERT( error );
		}
		ZEFIRO_LOG( "NORMAL" , "Thread::start() End" + toString());
		threadMutex_->unlock();
	}
	int Thread::getThreadID() const{
		threadMutex_->lock();
		int result = threadID_;
		threadMutex_->unlock();
		return result;
	}
	std::string Thread::getName() const{
		threadMutex_->lock();
		std::string result = name_;
		threadMutex_->unlock();
		return result;
	}
	int Thread::getPriority() const{
		int result;
		threadMutex_->lock();
		if( THREAD_PRIORITY_ERROR_RETURN == ( result = GetThreadPriority( thread_ ) ) ){
			threadMutex_->unlock();
			WIN32ASSERT( GetLastError() );
		}
		threadMutex_->unlock();
		return result;
	}
	void Thread::setPriority( int priority ){
		ZEFIRO_STD_ASSERT( priority >= 0 );
		threadMutex_->lock();
		if( 0 == SetThreadPriority( thread_ , priority ) ){
			threadMutex_->unlock();
			WIN32ASSERT( GetLastError() );
		}
		threadMutex_->unlock();
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
		ZEFIRO_LOG( "NORMAL" , "Thread::exit() Begin");
		Thread *currentThread = getCurrentThread();
		currentThread->threadMutex_->lock();
		if( ! currentThread->joinable_ ){
			if( currentThread->canRemoveRunnable_ ){
				delete currentThread->runnable_;
			}
			currentThread->threadMutex_->unlock();
			delete currentThread;
		}else{
			currentThread->threadMutex_->unlock();
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
		threadMutex_->lock();
		ZEFIRO_LOG( "NORMAL" , "Thread::Thread( Runnable *, int ) Begin" + toString());
		if( NULL == (thread_ = (HANDLE)_beginthreadex( NULL , stackSize , (unsigned (__stdcall *)(void *))runProc , this , CREATE_SUSPENDED , &threadID_ ) ) ){
			constructError_ = GetLastError();	//	コンストラクタ内で例外は発生させたくないので、エラーを記憶
		}
		threads__.push_back( this );
		ZEFIRO_LOG( "NORMAL" , "Thread::Thread( Runnable *, int ) END" + toString() );
		threadMutex_->unlock();
		threadsMutex__.unlock();
	}
	int Thread::doJoin( int millisecond ){
		ZEFIRO_STD_ASSERT( millisecond >= 0 );
		threadMutex_->lock();
		ZEFIRO_LOG( "NORMAL" , "Thread::join() Begin" + toString());
		if( !isAvailable() ){
			ZEFIRO_LOG( "ERROR" , "Thread::join()" + toString());
			threadMutex_->unlock();
			WIN32ASSERT( constructError_ );
		}
		threadMutex_->unlock();
		DWORD result = WaitForSingleObject( thread_ , millisecond );
		threadMutex_->lock();
		switch( result ){
		case WAIT_ABANDONED:
		case WAIT_OBJECT_0:
			break;
		case WAIT_TIMEOUT:
			ZEFIRO_LOG( "NORMAL" , "Thread::join() End" + toString());
			threadMutex_->unlock();
			throw TimeOutException();
		case WAIT_FAILED:
			ZEFIRO_LOG( "ERROR" , "Thread::join()" + toString());
			WIN32ASSERT( GetLastError() );
		}
		DWORD exitCode;
		if( 0 == GetExitCodeThread( thread_ , &exitCode ) ){
			threadMutex_->unlock();
			ZEFIRO_LOG( "ERROR" , "Thread::join()" + toString());
			WIN32ASSERT( GetLastError() );
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
		threadMutex_(new Mutex),hasStarted_(true),
		joinable_(false),canRemoveRunnable_(false),name_("main"){
		ZEFIRO_LOG( "NORMAL" , "Thread::Thread( HANDLE , unsigned int )" + toString());
	}
	Thread::~Thread(){
		ZEFIRO_LOG( "NORMAL" , "Thread::~Thread() Begin" + toString());
		threadsMutex__.lock();
		removeThread( this );
		threadsMutex__.unlock();
		if( isAvailable() ){
			delete threadMutex_;
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