/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/include/std/Attic/UniqueNumberFactory.h,v 1.4 2002/04/29 16:28:42 ama Exp $
 */

#ifndef __UNIQUENUMBERFACTORY_H__
#define __UNIQUENUMBERFACTORY_H__

#include <vector>

#include "std/UniqueNumberBadAlloc.h"

namespace zefiro_std{
	/**	���j�[�N�i���o�[�����N���X�B
	 *	��x�A�������ꂽ�i���o�[�͍폜���Ȃ����萶������Ȃ��B
	 *	�폜���ꂽ�i���o�[�͋L������A�ė��p�����B
	 */
	class UniqueNumberFactory
	{
	public:
		/** �R���X�g���N�^
		 * \param begin_number ���j�[�N�i���o�[�̊J�n�ԍ�
		 */
		UniqueNumberFactory( int begin_number = 0 );
		///	�f�X�g���N�^
		virtual ~UniqueNumberFactory();
		/**
		 * ���j�[�N�i���o�[�̐���
		 *	\return �������ꂽ���j�[�N�i���o�[
		 * \throw zefiro_std::unique_number_bad_alloc ���j�[�N�i���o�[�̐����͈͂𒴂��鐶�����s�����B
		 */
		virtual int createNumber() throw(zefiro_std::UniqueNumberBadAlloc);			
		/**
		 *	���j�[�N�i���o�[�̍폜
		 *	\param number �폜���郆�j�[�N�i���o�[
		 */
		virtual void deleteNumber( int number );
	protected:
		/**
		 * �폜�������j�[�N�i���o�[�̏W����number�͊܂܂�邩���肷��B
		 * \param number �폜�������j�[�N�i���o�[�̏W���Ɋ܂܂�邩���肷��i���o�[
		 * \retval true �폜�������j�[�N�i���o�[�̏W���Ɋ܂܂��B
		 * \retval false �폜�������j�[�N�i���o�[�̏W���Ɋ܂܂�Ȃ��B
		 * \throw std::invalid_argument ���p���Ă��Ȃ����j�[�N�i���o�[���w�肵���B
		*/
		virtual bool isContainedInDeletedUniqueNumbers( int number ) throw(std::invalid_argument);
		/**
		 * ���p����Ă��郆�j�[�N�i���o�[�Ɋ܂܂�邩���肷��B
		 * \param number ���p���Ă��邩���肷�郆�j�[�N�i���o�[
		 * \retval true number�̃��j�[�N�i���o�[�͗��p����Ă���B
		 * \retval false number�̃��j�[�N�i���o�[�͗��p����Ă��Ȃ��B
		 */
		virtual bool isContainedInUsedUniqueNumbers( int number );
		std::vector<int>	_deletedUniqueNumbers;		///<	�폜�������j�[�N�i���o�[�̏W��
		int					_maxUniqueNumber;			///<	�ő�̃��j�[�N�i���o�[
	};
};
#endif //__UNIQUENUMBERFACTORY_H__