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
		// TODO: �X���b�h�I�����̃R�[���o�b�N�֐���ǉ��ł���悤�ɂ��ׂ������B
		// TODO: threads�̓V���O���g���ɂ��Ă����ׂ������B
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
			* �X���b�h���R���X�g���N�g����B
			*/
			void create( int stackSize );
			/**
			* �X���b�h��Join����B
			*/
			int doJoin( int millisecond ); 
			/**
			* ���C���X���b�h�p�R���X�g���N�^
			*/
			Thread( HANDLE thread , unsigned int threadid );
			/**
			* �f�X�g���N�^
			* �X���b�h��join����邩exit�����܂Ńf�X�g���N�g����Ȃ��̂ŁAprotected�Ƃ���B
			* ���̂悤�ɂ��邱�ƂŁA�K��Thread��new�Ń������m�ۂ��Ȃ���΂Ȃ�Ȃ��Ȃ�B
			*/
			virtual ~Thread();
			/**
			* �X���b�h�̎��s��B
			* thread->run()��thread->_runnable->run()�����s����B
			* \param thread ���s������X���b�h
			* \return �K��0�ƂȂ�B
			*/
			static int runProc( Thread *thread );
		private:
			class Threads : public ClassLevelCountedLockable< Threads > {
				::std::vector<Thread *> threads_;
			public:
				/**
				* �o�^���Ă���X���b�h���폜����B
				* \param thread �폜����X���b�h
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
				* �o�^���Ă��錻�݂̃X���b�h�̃C�e���[�^��Ԃ��B
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
				* ���C���X���b�h�̓o�^
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
		// �X���b�h�Ɨ��ȕϐ�����������e���v���[�g�N���X
		/**

		�����̃X���b�h����Q�Ƃ���郁���o�ϐ����X���b�h�Ɨ��ɂ������ꍇ�ȂǂɎg���B
		��F
		class A{
		public:
			void set( int x ){
				val_ = x;	//	set���Ăяo���X���b�h�ɂ����x���i�[�����ꏊ�͈Ⴄ�B�����X���b�h�̏ꍇ�̂ݓ����ϐ��ɃA�N�Z�X�ł���B
			}
			int get(){
				return val_;// get���Ăяo���X���b�h�ɂ����val�̒l�͈Ⴄ�B�����X���b�h�̏ꍇ�̂ݓ����ϐ��ɃA�N�Z�X�ł���B
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
		* �R���X�g���N�^
		* \param stackSize �X���b�h�Ŋm�ۂ���X�^�b�N�̃T�C�Y(0�ɂ���ƁA�Ăяo�����X���b�h�Ɠ����T�C�Y�ɂȂ�B)
		* \param name �X���b�h�ɂ����O
		* \param runnable �X���b�h�ŌĂяo��run���\�b�h�̂���I�u�W�F�N�g�AThread��h���������Ɏg���ꍇ�w�肷��B
�@		*/		
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
		* �X���b�h�̗��p�\����
		* \retval true �X���b�h�I�u�W�F�N�g�͗��p�\�ł���B
		* \retval false �@�X���b�h�I�u�W�F�N�g�͗��p�s�\�ł���B
		*/
		bool Thread::isAvailable(){
			Lock lock(*this);
			return thread_ != NULL;
		}
		/**
		* �X���b�h��Join�\����
		* <ul>
		*  <li>Join�\�ȃX���b�h�͕K��Join���Ȃ���΂Ȃ�Ȃ��B
		* ����Join���Ȃ��ꍇ�́A���\�[�X���[�N����������B</li>
		*  <li>Join�s�\�ȃX���b�h��Join���Ă͂Ȃ�Ȃ��B
		* Join�s�\�ȃX���b�h�I�u�W�F�N�g�̓X���b�h�̏I����(exit)��
		* ��������������B���������āAstart()���ꂽ��̂����Ȃ鎞�_�ł�
		* ���������������邨���ꂪ����̂ŁA���̃��b�h�I�u�W�F�N�g�ɃA�N
		* �Z�X���邱�Ƃ͊댯�ł���B
		* </li>
		* </ul>
		* \retval true Join�\
		* \retval false Join�s�\
		*/
		bool Thread::isJoinable(){
			Lock lock(*this);
			return joinable_;
		}
		/**
		* �X���b�h��Join�\�ݒ�B
		* ���̃��\�b�h��start()���Ă΂��O�ɌĂ΂Ȃ���΂Ȃ�Ȃ��B
		* \param joinable
		* <ul>
		*	<li>true Join�\ </li>
		*	<li>false Join�s�\ </li>
		* </ul>
		*/
		void Thread::setJoinable( bool joinable ){
			Lock lock(*this);
			joinable_ = joinable;	
		}
		/**
		* Runnable�I�u�W�F�N�g�̏��L���̎擾
		* Joinable�łȂ��Ƃ��ɁARunnable���폜���邩�H
		*/
		bool Thread::canRemoveRunnable(){
			Lock lock(*this);
			return canRemoveRunnable_;
		}
		/**
		* Runnable�I�u�W�F�N�g�̏��L���̐ݒ�
		* setJoinable��false�̎���canRemoveRunnable��true���ƁAThread::exit()�����Ƃ��ɁA
		* Thread�̏��L����Runnable���f�X�g���N�g����B
		* ����ȊO�̎��ɂ�Runnable��Thread�ɂ���ăf�X�g���N�g����Ȃ��B
		* \param canRemoveRunnable Joinable�łȂ��Ƃ���Runnable���f�X�g���N�g����B
		*/
		void Thread::setCanRemoveRunnable( bool canRemoveRunnable ){
			Lock lock(*this);
			canRemoveRunnable_ = canRemoveRunnable;
		}
		/**
		* �X���b�h���J�n����B
		* ��x�A�J�n�����X���b�h���ĂъJ�n���邱�Ƃ͂ł��Ȃ��B�����Ă�start���Ă΂ꂽ��A
		* IllegalThreadStateException���Ă΂��B
		* \throw IllegalThreadStateException �ُ�ȃX���b�h��ԗ�O�����������B
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
		* �X���b�hID��Ԃ��B
		* \return �X���b�hID
		*/
		int Thread::getThreadID(){
			Lock lock(*this);
			return threadID_;
		}
		/**
		* �X���b�h�̖��O��Ԃ��B
		* \return �X���b�h�̖��O�B���̖��O�̓��[�U���R���X�g���N�^�Ŏw�肵�����O�ƂȂ�B
		*/
		::std::string Thread::getName(){
			Lock lock(*this);
			return name_;
		}
		/**
		* �X���b�h�̗D��x��Ԃ��B
		* \return �X���b�h�̗D��x
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
		* �X���b�h�̗D��x��ݒ肷��B
		* \param priority �X���b�h�̗D��x
		* \throw Win32Exception
		*/
		void Thread::setPriority( int priority ){
			Lock lock(*this);
			if( 0 == SetThreadPriority( thread_ , priority ) ){
				PSS_THROW_PARAM1( ::pss::std::Win32Error(GetLastError()) , "");
			}
		}
		/**
		* �X���b�h�̌����B
		* �X���b�h���I������܂őҋ@����B
		* �X���b�h��Join�\�łȂ��ꍇ�̓���͕s��ł���B
		* \param millisecond �ő��millisecond�����ҋ@����B
		* \return �X���b�h���ŁAexit()�����Ƃ��̈���exitCode�ƂȂ�B
		* \throw TimeOutException �X���b�h��millisecond�����ҋ@���ă^�C���A�E�g�ɂȂ����Ƃ��ɔ�������B
		*/
		int Thread::join(){
			return doJoin( INFINITE );
		}
		int Thread::join( int millisecond ){

			return doJoin( millisecond );
		}
		/**
		* �X���b�h�̃^�C���X���C�X������B
		*/
		void Thread::yield(){
			Sleep(0);
		}
		/**
		* �X���b�h���X���[�v����B
		*/
		void Thread::sleep( int millisecond ){
			Sleep(millisecond);
		}
		typedef ::Loki::SingletonHolder< ::pss::system::ThreadLocals > SingleThreadLocals;
		/**
		* �X���b�h�̏I���B
		* �X���b�h�𒼂��ɏI��������B
		* \param exitCode exitCode��join()�����Ƃ��̖߂�l�ƂȂ�B
		* �X���b�h����exit���Ăяo�����ɃZ�b�g�����exitCode��0�ł���B
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
		* ���݂̃X���b�h�̃X���b�hID��Ԃ��B
		* \return ���݂̃X���b�h�̃X���b�hID
		*/
		int Thread::getCurrentThreadID(){
			return GetCurrentThreadId();
		}
		/**
		* ���݂̃X���b�h�̃X���b�h�I�u�W�F�N�g��Ԃ��B
		* ���̃X���b�h�I�u�W�F�N�g��delete���Ă͂Ȃ�Ȃ��B
		* \return ���݂̃X���b�h�̃X���b�h�I�u�W�F�N�g
		*/
		Thread* Thread::getCurrentThread(){
			return threads__.getCurrentThread();
		}
		/**
		* �X���b�h�̎��s��B
		* ���̃��b�\�h���I�[�o���C�h���邩Runnable��ݒ肵�A�X���b�h�̎��s���e���w�肷��B
		*/
		void Thread::run(){
		}
		/**
		* �X���b�h�̏�Ԃ𕶎���Ƃ��ĕԂ��B
		*/
		::std::string Thread::toString() const{
			::std::ostringstream	ostrstr;
			ostrstr << " Thread HANDLE = " << thread_ << " , Thread ID = " << threadID_ << " , hasStarted = " << hasStarted_ << " , joinable = " << joinable_ << " , name = " << name_ << " , canRemoveRunnable = " << canRemoveRunnable_ << " , constructError = " << constructError_;
			return ostrstr.str();
		}
		void Thread::create( int stackSize ){
			Threads::Lock lock;				//	�f�b�h���b�N������邽�߂ɕK�����̏��ԂŃ��b�N
			threads__.addMainThread();
			{
				Lock lock(*this);
				if( NULL == (thread_ = (HANDLE)_beginthreadex( NULL , stackSize , (unsigned (__stdcall *)(void *))runProc , this , CREATE_SUSPENDED , &threadID_ ) ) ){
					constructError_ = GetLastError();	//	�R���X�g���N�^���ŗ�O�͔������������Ȃ��̂ŁA�G���[���L��
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
