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
		 * �X���b�h�̗��p�\����
		 * \retval true �X���b�h�I�u�W�F�N�g�͗��p�\�ł���B
		 * \retval false �@�X���b�h�I�u�W�F�N�g�͗��p�s�\�ł���B
		 */
		bool isAvailable() const;
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
		bool isJoinable() const;
		/**
		 * �X���b�h��Join�\�ݒ�B
		 * ���̃��\�b�h��start()���Ă΂��O�ɌĂ΂Ȃ���΂Ȃ�Ȃ��B
		 * \param joinable
		 * <ul>
		 *	<li>true Join�\ </li>
		 *	<li>false Join�s�\ </li>
		 * </ul>
		 */
		void setJoinable( bool joinable );
		/**
		 * �X���b�hID��Ԃ��B
		 * \return �X���b�hID
		 */
		int getThreadID() const;
		/**
		 * �X���b�h�̗D��x��Ԃ��B
		 * \return �X���b�h�̗D��x
		 */
		int getPriority() const;
		/**
		 * �X���b�h�̗D��x��ݒ肷��B
		 * \param priority �X���b�h�̗D��x
		 */
		void setPriority( int priority );
		/**
		 * �X���b�h���J�n����B
		 * ��x�A�J�n�����X���b�h���ĂъJ�n���邱�Ƃ͂ł��Ȃ��B�����Ă�start���Ă΂ꂽ��A
		 * IllegalThreadStateException���Ă΂��B
		 * \throw IllegalThreadStateException �ُ�ȃX���b�h��ԗ�O�����������B
		 */
		void start();
		/**
		 * �X���b�h�̌����B
		 * �X���b�h���I������܂őҋ@����B
		 * �X���b�h��Join�\�łȂ��ꍇ�̓���͕s��ł���B
		 * \return �X���b�h���ŁAexit()�����Ƃ��̈���exitCode�ƂȂ�B
		 */
		int join();
		/**
		 * �X���b�h�̃^�C���X���C�X������B
		 */
		static void yield();
		/**
		 * �X���b�h���X���[�v����B
		 */
		static void sleep( int millisecond );
		/**
		 * �X���b�h�̏I���B
		 * �X���b�h�𒼂��ɏI��������B
		 * \param exitCode exitCode��join()�����Ƃ��̖߂�l�ƂȂ�B
		 * �X���b�h����exit���Ăяo�����ɃZ�b�g�����exitCode��0�ł���B
		 */
		static void exit( int exitCode );
		/**
		 * ���݂̃X���b�h�̃X���b�hID��Ԃ��B
		 * \return ���݂̃X���b�h�̃X���b�hID
		 */
		static int getCurrentThreadID();
		/**
		 * ���݂̃X���b�h�̃X���b�h�I�u�W�F�N�g��Ԃ��B
		 * ���̃X���b�h�I�u�W�F�N�g��delete���Ă͂Ȃ�Ȃ��B
		 * \return ���݂̃X���b�h�̃X���b�h�I�u�W�F�N�g
		 */
		static Thread *getCurrentThread();
		/**
		 * �X���b�h�̎��s��B
		 * ���̃��b�\�h���I�[�o���C�h���邩Runnable��ݒ肵�A�X���b�h�̎��s���e���w�肷��B
		 */
		virtual void run();
		/**
		 * �X���b�h�̏�Ԃ𕶎���Ƃ��ĕԂ��B
		 */
		virtual std::string toString() const;

	protected:
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
		/**
		 * __threads�ɓo�^���Ă��錻�݂̃X���b�h�̃C�e���[�^��Ԃ��B
		 */
		static std::vector<Thread*>::iterator getCurrentThreadIterator();
		/**
		 * __threads�ɓo�^���Ă���X���b�h���폜����B
		 * \param thread �폜����X���b�h
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