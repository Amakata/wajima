#pragma once

#include <windows.h>
#include <string>
#include <list>
#include <map>
#include <vector>
#include <sstream>
#include <process.h>
#include <loki/SmartPtr.h>
#include <loki/Singleton.h>

#include "Runnable.hpp"
#include "Mutex.hpp"
#include "IllegalThreadStateException.hpp"
#include "TimeOutException.hpp"
#include "pss/std/Win32Exception.hpp"
#include "pss/std/Exception.hpp"
#include "ThreadingModel.hpp"

namespace pss {
	namespace system {
		// TODO: スレッド終了時のコールバック関数を追加できるようにすべきかも。
		// TODO: threadsはシングルトンにしておくべきかも。
		class Thread : public Runnable , public ObjectLevelCountedLockable<Thread>
		{
		public:
			Thread( int stackSize = 0 );
			Thread( ::std::string name , int stackSize = 0 );
			Thread( Runnable *runnable , int stackSize = 0 );
			Thread( Runnable *runnable , ::std::string name , int stackSize = 0 );
			bool isAvailable();
			bool isJoinable();
			void setJoinable( bool joinable );
			bool canRemoveRunnable();
			void setCanRemoveRunnable( bool canRemoveRunnable );
			int getThreadID();
			::std::string getName();
			int getPriority();
			void setPriority( int priority );
			void start();
			int join();
			int join( int millisecond );
			static void yield();
			static void sleep( int millisecond );
			static void exit( int exitCode );
			static int getCurrentThreadID();
			static Thread *getCurrentThread();
			virtual void run();
			virtual ::std::string toString() const;

			static const int NULLTHREAD;
		protected:
			/**
			* スレッドをコンストラクトする。
			*/
			void create( int stackSize );
			/**
			* スレッドをJoinする。
			*/
			int doJoin( int millisecond ); 
			/**
			* メインスレッド用コンストラクタ
			*/
			Thread( HANDLE thread , unsigned int threadid );
			/**
			* デストラクタ
			* スレッドはjoinされるかexitされるまでデストラクトされないので、protectedとする。
			* このようにすることで、必ずThreadはnewでメモリ確保しなければならなくなる。
			*/
			virtual ~Thread();
			/**
			* スレッドの実行先。
			* thread->run()かthread->_runnable->run()を実行する。
			* \param thread 実行先をもつスレッド
			* \return 必ず0となる。
			*/
			static int runProc( Thread *thread );
		private:
			class Threads : public ClassLevelCountedLockable< Threads > {
				::std::vector<Thread *> threads_;
			public:
				/**
				* 登録してあるスレッドを削除する。
				* \param thread 削除するスレッド
				*/
				void removeThread( Thread *thread ){
					Lock lock;
					::std::vector<Thread*>::iterator end = threads_.end();
					for( ::std::vector<Thread*>::iterator itr = threads_.begin() ; itr != end ; ++itr ){
						if( *itr == thread ){
							threads_.erase( itr );
							return;
						}
					}
				}
				/**
				* 登録してある現在のスレッドのイテレータを返す。
				*/
				::std::vector<Thread*>::iterator getCurrentThreadIterator(){
					int currentID = getCurrentThreadID();
					::std::vector<Thread*>::iterator end = threads_.end();
					for( ::std::vector<Thread*>::iterator itr = threads_.begin() ; itr != end ; ++itr ){
						if(  (*itr)->getThreadID() == currentID ){
							return itr;
						}
					}
					return end;
				}
				/**
				* メインスレッドの登録
				*/
				void addMainThread(){
					if( threads_.size() == 0 ){
						Thread *mainThread = new Thread( ::GetCurrentThread() , ::GetCurrentThreadId() );
						addThread( mainThread );
					}
				}

				void addThread( Thread* thread ){
					Lock lock;
					threads_.push_back( thread );
				}
				Thread* getCurrentThread(){ 
					Lock lock;
					addMainThread();
					::std::vector<Thread*>::iterator itr;
					Thread *result;
					if( threads_.end() != (itr = getCurrentThreadIterator() ) ){
						result = (*itr);
					}else{
						result = NULL;
					}
					return result;
				}
			};

			HANDLE	thread_;
			unsigned int	threadID_;
			Runnable *runnable_;
			DWORD	constructError_;
			bool	hasStarted_;
			bool	joinable_;
			bool	canRemoveRunnable_;
			::std::string	name_;
			static Threads threads__;
		};
		class ThreadLocalBase {
		public:
			virtual ~ThreadLocalBase(){}
			virtual void clear() = 0;
			virtual void clear( int threadId ) = 0;
		};

		class ThreadLocals {
			typedef ::std::list<ThreadLocalBase* > TLBList;
		public:
			virtual ~ThreadLocals(){
			}
			void add( ThreadLocalBase* val ){
				threadLocals_.push_back(val);
			}
			void del( ThreadLocalBase* val ){
				threadLocals_.remove( val );
			}
			void clear();
		private:
			friend ::Loki::CreateUsingNew<ThreadLocals>;
			ThreadLocals(){
			}
			TLBList threadLocals_;
		};
		// スレッド独立な変数を実現するテンプレートクラス
		/**

		複数のスレッドから参照されるメンバ変数をスレッド独立にしたい場合などに使う。
		例：
		class A{
		public:
			void set( int x ){
				val_ = x;	//	setを呼び出すスレッドによってxが格納される場所は違う。同じスレッドの場合のみ同じ変数にアクセスできる。
			}
			int get(){
				return val_;// getを呼び出すスレッドによってvalの値は違う。同じスレッドの場合のみ同じ変数にアクセスできる。
			}
		private:
		pss::system::ThreadLocal<int> val_;
		};
		*/
		template <typename T>
		class ThreadLocal : public ObjectLevelCountedLockable<ThreadLocal> , public ThreadLocalBase {
			typedef ::std::map< int , T* > ThreadLocalMap;
			typedef ::Loki::SingletonHolder< ThreadLocals ,::Loki::CreateUsingNew, ::Loki::DefaultLifetime, ::pss::system::ClassLevelCountedLockable > SingleThreadLocals;
		public:
			ThreadLocal(){
				ThreadLocals& tls = SingleThreadLocals::Instance();
				tls.add( this );
			}
			virtual ~ThreadLocal(){
				ThreadLocals& tls = SingleThreadLocals::Instance();
				tls.del( this );
			}
			operator T&() {
				Lock lock(*this);
				return *get();
			}
			const T& operator = (const T& t){
				Lock lock(*this);
				set(t);
				return *get();
			}
			virtual void clear(){
				Lock lock(*this);
				erase( Thread::getCurrentThreadID() );
			}
			virtual void clear( int threadId ){
				Lock lock(*this);
				erase( threadId );
			}
			bool empty(){
				ThreadLocalMap::iterator it = vals_.find( Thread::getCurrentThreadID() );
				return it == vals_.end();
			}
		private:
			T* get(){
				ThreadLocalMap::iterator it = vals_.find( Thread::getCurrentThreadID() );
				T* result;
				if( it != vals_.end() ){
					result = it->second;
				}else{
					result = new T;
					vals_.insert( ::std::pair<int,T* >(Thread::getCurrentThreadID(),result));
				}

				return result;
			}
			void set( const T& t ){
				ThreadLocalMap::iterator it = vals_.find( Thread::getCurrentThreadID() );
				if( it != vals_.end() ){
					*(it->second) = t;
				}else{
					T* p = new T;
					*p = t;
					vals_.insert( ::std::pair<int,T*>(Thread::getCurrentThreadID(),p));
				}
			}
			void erase( int threadId ){
				ThreadLocalMap::iterator it = vals_.find( threadId );
				if( it != vals_.end() ){
					vals_.erase( it );
				}
			}
			ThreadLocalMap	vals_;
		};
#ifndef PSS_SYSTEM_THRED_COMPILE
		const int Thread::NULLTHREAD = -1;
		Thread::Threads Thread::threads__;

		/**
		* コンストラクタ
		* \param stackSize スレッドで確保するスタックのサイズ(0にすると、呼び出し側スレッドと同じサイズになる。)
		* \param name スレッドにつく名前
		* \param runnable スレッドで呼び出すrunメソッドのあるオブジェクト、Threadを派生させずに使う場合指定する。
　		*/		
		Thread::Thread( int stackSize )
			:runnable_(NULL),thread_(NULL),threadID_(0),constructError_(0),hasStarted_(false),joinable_(true),canRemoveRunnable_(true),name_(""){
			create( stackSize );
		}
		Thread::Thread( ::std::string name , int stackSize )
			:runnable_(NULL),thread_(NULL),threadID_(0),constructError_(0),hasStarted_(false),joinable_(true),canRemoveRunnable_(true),name_(name){
			create( stackSize );
		}
		Thread::Thread( Runnable *r , int stackSize )
			:runnable_(r),thread_(NULL),threadID_(0),constructError_(0),hasStarted_(false),joinable_(true),canRemoveRunnable_(true),name_(""){
			create( stackSize );
		}
		Thread::Thread( Runnable *r , ::std::string name , int stackSize )
			:runnable_(r),thread_(NULL),threadID_(0),constructError_(0),hasStarted_(false),joinable_(true),canRemoveRunnable_(true),name_(name){
			create( stackSize );
		}
		/**
		* スレッドの利用可能判定
		* \retval true スレッドオブジェクトは利用可能である。
		* \retval false 　スレッドオブジェクトは利用不可能である。
		*/
		bool Thread::isAvailable(){
			Lock lock(*this);
			return thread_ != NULL;
		}
		/**
		* スレッドのJoin可能判定
		* <ul>
		*  <li>Join可能なスレッドは必ずJoinしなければならない。
		* もしJoinしない場合は、リソースリークが発生する。</li>
		*  <li>Join不可能なスレッドはJoinしてはならない。
		* Join不可能なスレッドオブジェクトはスレッドの終了時(exit)に
		* メモリ解放される。したがって、start()された後のいかなる時点でも
		* メモリ解放がされるおそれがあるので、そのレッドオブジェクトにアク
		* セスすることは危険である。
		* </li>
		* </ul>
		* \retval true Join可能
		* \retval false Join不可能
		*/
		bool Thread::isJoinable(){
			Lock lock(*this);
			return joinable_;
		}
		/**
		* スレッドのJoin可能設定。
		* このメソッドはstart()が呼ばれる前に呼ばなければならない。
		* \param joinable
		* <ul>
		*	<li>true Join可能 </li>
		*	<li>false Join不可能 </li>
		* </ul>
		*/
		void Thread::setJoinable( bool joinable ){
			Lock lock(*this);
			joinable_ = joinable;	
		}
		/**
		* Runnableオブジェクトの所有権の取得
		* Joinableでないときに、Runnableを削除するか？
		*/
		bool Thread::canRemoveRunnable(){
			Lock lock(*this);
			return canRemoveRunnable_;
		}
		/**
		* Runnableオブジェクトの所有権の設定
		* setJoinableがfalseの時にcanRemoveRunnableがtrueだと、Thread::exit()したときに、
		* Threadの所有するRunnableをデストラクトする。
		* それ以外の時にはRunnableはThreadによってデストラクトされない。
		* \param canRemoveRunnable JoinableでないときにRunnableをデストラクトする。
		*/
		void Thread::setCanRemoveRunnable( bool canRemoveRunnable ){
			Lock lock(*this);
			canRemoveRunnable_ = canRemoveRunnable;
		}
		/**
		* スレッドを開始する。
		* 一度、開始したスレッドを再び開始することはできない。もし再びstartが呼ばれたら、
		* IllegalThreadStateExceptionが呼ばれる。
		* \throw IllegalThreadStateException 異常なスレッド状態例外が発生した。
		* \throw Win32Exception
		*/
		void Thread::start(){
			Lock lock(*this);
			if( !isAvailable() ){
				PSS_THROW_PARAM1( ::pss::std::Win32Error(constructError_) , "");
			}
			if( !hasStarted_ ){
				hasStarted_ = true;
			}else{
				throw IllegalThreadStateException();
			}
			if( -1 == ResumeThread( thread_ ) ){
				PSS_THROW_PARAM1( ::pss::std::Win32Error(GetLastError()) , "");
			}
		}
		/**
		* スレッドIDを返す。
		* \return スレッドID
		*/
		int Thread::getThreadID(){
			Lock lock(*this);
			return threadID_;
		}
		/**
		* スレッドの名前を返す。
		* \return スレッドの名前。この名前はユーザがコンストラクタで指定した名前となる。
		*/
		::std::string Thread::getName(){
			Lock lock(*this);
			return name_;
		}
		/**
		* スレッドの優先度を返す。
		* \return スレッドの優先度
		* \throw Win32Exception
		*/
		int Thread::getPriority(){
			Lock lock(*this);
			int result;
			if( THREAD_PRIORITY_ERROR_RETURN == ( result = GetThreadPriority( thread_ ) ) ){
				PSS_THROW_PARAM1( ::pss::std::Win32Error(GetLastError()) , "");
			}
			return result;
		}
		/**
		* スレッドの優先度を設定する。
		* \param priority スレッドの優先度
		* \throw Win32Exception
		*/
		void Thread::setPriority( int priority ){
			Lock lock(*this);
			if( 0 == SetThreadPriority( thread_ , priority ) ){
				PSS_THROW_PARAM1( ::pss::std::Win32Error(GetLastError()) , "");
			}
		}
		/**
		* スレッドの結合。
		* スレッドが終了するまで待機する。
		* スレッドがJoin可能でない場合の動作は不定である。
		* \param millisecond 最大でmillisecondだけ待機する。
		* \return スレッド内で、exit()したときの引数exitCodeとなる。
		* \throw TimeOutException スレッドがmillisecondだけ待機してタイムアウトになったときに発生する。
		*/
		int Thread::join(){
			return doJoin( INFINITE );
		}
		int Thread::join( int millisecond ){

			return doJoin( millisecond );
		}
		/**
		* スレッドのタイムスライスを譲る。
		*/
		void Thread::yield(){
			Sleep(0);
		}
		/**
		* スレッドをスリープする。
		*/
		void Thread::sleep( int millisecond ){
			Sleep(millisecond);
		}
		typedef ::Loki::SingletonHolder< ::pss::system::ThreadLocals > SingleThreadLocals;
		/**
		* スレッドの終了。
		* スレッドを直ちに終了させる。
		* \param exitCode exitCodeはjoin()したときの戻り値となる。
		* スレッドからexitを呼び出さずにセットされるexitCodeは0である。
		*/
		void Thread::exit( int exitCode ){
			bool joinable;
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
			ThreadLocals tls = SingleThreadLocals::Instance();
			tls.clear();
			if( !joinable){
				delete currentThread;
			}
			_endthreadex( exitCode );
		}
		/**
		* 現在のスレッドのスレッドIDを返す。
		* \return 現在のスレッドのスレッドID
		*/
		int Thread::getCurrentThreadID(){
			return GetCurrentThreadId();
		}
		/**
		* 現在のスレッドのスレッドオブジェクトを返す。
		* このスレッドオブジェクトはdeleteしてはならない。
		* \return 現在のスレッドのスレッドオブジェクト
		*/
		Thread* Thread::getCurrentThread(){
			return threads__.getCurrentThread();
		}
		/**
		* スレッドの実行先。
		* このメッソドをオーバライドするかRunnableを設定し、スレッドの実行内容を指定する。
		*/
		void Thread::run(){
		}
		/**
		* スレッドの状態を文字列として返す。
		*/
		::std::string Thread::toString() const{
			::std::ostringstream	ostrstr;
			ostrstr << " Thread HANDLE = " << thread_ << " , Thread ID = " << threadID_ << " , hasStarted = " << hasStarted_ << " , joinable = " << joinable_ << " , name = " << name_ << " , canRemoveRunnable = " << canRemoveRunnable_ << " , constructError = " << constructError_;
			return ostrstr.str();
		}
		void Thread::create( int stackSize ){
			Threads::Lock lock;				//	デッドロックを避けるために必ずこの順番でロック
			threads__.addMainThread();
			{
				Lock lock(*this);
				if( NULL == (thread_ = (HANDLE)_beginthreadex( NULL , stackSize , (unsigned (__stdcall *)(void *))runProc , this , CREATE_SUSPENDED , &threadID_ ) ) ){
					constructError_ = GetLastError();	//	コンストラクタ内で例外は発生させたくないので、エラーを記憶
				}
				threads__.addThread( this );
			}
		}
		int Thread::doJoin( int millisecond ){
			DWORD exitCode;
			HANDLE thread;
			{
				Lock lock(*this);
				if( !isAvailable() ){
					PSS_THROW_PARAM1( ::pss::std::Win32Error(constructError_) , "");
				}
				thread = thread_;
			}
			DWORD result = WaitForSingleObject( thread , millisecond );
			{
				Lock lock(*this);
				switch( result ){
				case WAIT_ABANDONED:
				case WAIT_OBJECT_0:
					break;
				case WAIT_TIMEOUT:
					throw TimeOutException();
				case WAIT_FAILED:
					PSS_THROW_PARAM1( ::pss::std::Win32Error(GetLastError()) , "");
				}
				if( 0 == GetExitCodeThread( thread_ , &exitCode ) ){
					PSS_THROW_PARAM1( ::pss::std::Win32Error(GetLastError()) , "");
				}
			}
			delete this;
			return exitCode;
		}
		Thread::Thread( HANDLE thread , unsigned int threadid )
			:thread_(thread),threadID_(threadid),
			runnable_(false),constructError_(0),
			hasStarted_(true),
			joinable_(false),canRemoveRunnable_(false),name_("main"){
		}
		Thread::~Thread(){
			threads__.removeThread( this );
			if( isAvailable() ){
				CloseHandle( thread_ );
			}
		}
		int Thread::runProc( Thread *thread ){
			if( thread->runnable_ == NULL ){
				thread->run();
			}else{
				thread->runnable_->run();
			}
			Thread::exit(0);
			return 0;
		}
		void ThreadLocals::clear(){
			int currentThreadId = ::pss::system::Thread::getCurrentThreadID();
			TLBList::iterator end = threadLocals_.end();
			for( TLBList::iterator it = threadLocals_.begin() ; it != end ; ++it ){
				(*it)->clear( currentThreadId );
			}
		}
#endif
	}
}
