#ifndef __THREAD_H__
#define __THREAD_H__
/**
 * $ Header: $
 */

#include <windows.h>
#include <string>
#include <vector>

#include "thread/Runnable.h"
#include "thread/Mutex.h"
#include "thread/IllegalThreadStateException.h"
#include "std/sys/Win32Assert.h"

namespace zefiro_thread {
	class Thread : public Runnable
	{
	public:
		Thread( int stackSize = 0 );
		Thread( std::string name , int stackSize = 0 );
		Thread( Runnable *runnable , int stackSize = 0 );
		Thread( Runnable *runnable , std::string name , int stackSize = 0 );
		/**
		 * スレッドの利用可能判定
		 * \retval true スレッドオブジェクトは利用可能である。
		 * \retval false 　スレッドオブジェクトは利用不可能である。
		 */
		bool isAvailable() const;
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
		bool isJoinable() const;
		/**
		 * スレッドのJoin可能設定。
		 * このメソッドはstart()が呼ばれる前に呼ばなければならない。
		 * \param joinable
		 * <ul>
		 *	<li>true Join可能 </li>
		 *	<li>false Join不可能 </li>
		 * </ul>
		 */
		void setJoinable( bool joinable );
		/**
		 * スレッドIDを返す。
		 * \return スレッドID
		 */
		int getThreadID() const;
		/**
		 * スレッドの優先度を返す。
		 * \return スレッドの優先度
		 */
		int getPriority() const;
		/**
		 * スレッドの優先度を設定する。
		 * \param priority スレッドの優先度
		 */
		void setPriority( int priority );
		/**
		 * スレッドを開始する。
		 * 一度、開始したスレッドを再び開始することはできない。もし再びstartが呼ばれたら、
		 * IllegalThreadStateExceptionが呼ばれる。
		 * \throw IllegalThreadStateException 異常なスレッド状態例外が発生した。
		 */
		void start();
		/**
		 * スレッドの結合。
		 * スレッドが終了するまで待機する。
		 * スレッドがJoin可能でない場合の動作は不定である。
		 * \return スレッド内で、exit()したときの引数exitCodeとなる。
		 */
		int join();
		/**
		 * スレッドのタイムスライスを譲る。
		 */
		static void yield();
		/**
		 * スレッドをスリープする。
		 */
		static void sleep( int millisecond );
		/**
		 * スレッドの終了。
		 * スレッドを直ちに終了させる。
		 * \param exitCode exitCodeはjoin()したときの戻り値となる。
		 * スレッドからexitを呼び出さずにセットされるexitCodeは0である。
		 */
		static void exit( int exitCode );
		/**
		 * 現在のスレッドのスレッドIDを返す。
		 * \return 現在のスレッドのスレッドID
		 */
		static int getCurrentThreadID();
		/**
		 * 現在のスレッドのスレッドオブジェクトを返す。
		 * このスレッドオブジェクトはdeleteしてはならない。
		 * \return 現在のスレッドのスレッドオブジェクト
		 */
		static Thread *getCurrentThread();
		/**
		 * スレッドの実行先。
		 * このメッソドをオーバライドするかRunnableを設定し、スレッドの実行内容を指定する。
		 */
		virtual void run();
		/**
		 * スレッドの状態を文字列として返す。
		 */
		virtual std::string toString() const;

	protected:
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
		/**
		 * __threadsに登録してある現在のスレッドのイテレータを返す。
		 */
		static std::vector<Thread*>::iterator getCurrentThreadIterator();
		/**
		 * __threadsに登録してあるスレッドを削除する。
		 * \param thread 削除するスレッド
		 */
		static void removeThread( Thread *thread );
		HANDLE	thread_;
		DWORD	threadID_;
		Runnable *runnable_;
		DWORD	constructError_;
		Mutex	*threadMutex_;
		bool	start_;
		bool	joinable_;
		static Mutex threadsMutex__;
		static std::vector<Thread *>	threads__;
	};
};


#endif //__THREAD_H__