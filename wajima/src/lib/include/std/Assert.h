#ifndef __ASSERT_H__
#define __ASSERT_H__

#include <std/Exception.h>
#include <std/NotEqualException.h>
#include <sstream>

namespace zefiro_std{
	/** �\���̓����N���X
	 *	�\���Ŕ�r������I�u�W�F�N�g�̕ϊ����s���B
	 */
	template <class T>
	struct assertion_traits
	{
		static bool equal( const T& x, const T& y )
		{
			return x == y;
		}
		/**
		 * x ������ɕϊ�����I�u�W�F�N�g
		 */
		static std::string toString( const T& x ){
			std::ostringstream oss;
			oss << x;
			return oss.str();
		}
	};

	/**
	 *	�\���B
	 *	�v���O�������ł̏����`�F�b�N�Ȃǂɗp����B
	 */
	namespace Assert {
		/**
		 * �\���̎���
		 * �Ăяo����āAcondition��������false�Ȃ�zefiro_std::Exception��throw�����B
		 * \param condition �]���̌���
		 * \param conditionExpression �]����
		 * \param lineNumber	�]�������\�[�X�t�@�C���̍s�ԍ�
		 * \param fileName		�]�������\�[�X�t�@�C����	
		 * \throw zefiro_std::Exception ��Ԃ�false�������B
		 */
		void assertImplementation( bool         condition, 
			                       std::string  conditionExpression = "",
				                   long lineNumber = Exception::UNKNOWNLINENUMBER,
					               std::string  fileName = Exception::UNKNOWNFILENAME );
		/**
		 * �񓙉����̕\���̎����B
		 * �Ăяo�����ƕK��zefiro_std::NotEqualException��throw�����B
		 * \param expected �\�z�l
		 * \param actual ���ݒl
		 * \param lineNumber	�]�������\�[�X�t�@�C���̍s�ԍ�
		 * \param fileName		�]�������\�[�X�t�@�C����	
		 * \throw zefiro_std::NotEqualException �K����������B
		*/
		void assertNotEqualImplementation( std::string expected,
			                               std::string actual,
						                   long lineNumber = Exception::UNKNOWNLINENUMBER,
								           std::string  fileName = Exception::UNKNOWNFILENAME );
		/**
		 * �����̕\��
		 * expected��actual�̒l���r���A�����łȂ���΁Azefiro_std::NotEqualException�𔭐�������B
		 * \param expected �\�z�l
		 * \param actual ���ݒl
		 * \param lineNumber	�]�������\�[�X�t�@�C���̍s�ԍ�
		 * \param fileName		�]�������\�[�X�t�@�C����		 
		 * \throw zefiro_std::NotEqualException �\�z�l�ƌ��ݒl���قȂ����B
		 */
		template <class T>
		void assertEquals(	const T& expected ,
							const T& actual ,
							long lineNumber = Exception::UNKNOWNLINENUMBER,
							std::string  fileName = Exception::UNKNOWNFILENAME ){
			if( ! assertion_traits<T>::equal( expected , actual ) ){
				assertNotEqualImplementation( assertion_traits<T>::toString(expected) , assertion_traits<T>::toString(actual) , lineNumber , fileName );
			}
		}
		/**
		 * �����̕\��
		 * expected��actual�̒l���r���A���̐�Βl��delta�ȉ��łȂ���΁A
		 * zefiro_std::NotEqualException�𔭐�������B
		 * \param expected �\�z�l
		 * \param actual ���ݒl
		 * \param delta ���e�덷
		 * \param lineNumber	�]�������\�[�X�t�@�C���̍s�ԍ�
		 * \param fileName		�]�������\�[�X�t�@�C����		 
		 * \throw zefiro_std::NotEqualException �\�z�l�ƌ��ݒl�̍��̐�Βl��delta��葽���������B
		 */
		void assertEquals(	double expected ,
							double actual ,
							double delta ,
							long lineNumber = Exception::UNKNOWNLINENUMBER,
							std::string  fileName = Exception::UNKNOWNFILENAME );
	}; // namespace Assert

/// �\���̃}�N��
#	define ZEFIRO_STD_ASSERT( condition )\
	(zefiro_std::Assert::assertImplementation((condition),(#condition),\
		__LINE__,__FILE__))

/// �\���̃}�N���i���b�Z�[�W�w��t�j
#	define ZEFIRO_STD_ASSERT_MESSAGE( message , condition )\
	(zefiro_std::Assert::assertImplementation( condition, \
												message, \
												__LINE__,\
												__FILE__ ) )
/// �\���̃}�N��(�����]��)
#	define ZEFIRO_STD_ASSERT_EQUAL( expected , actual )\
	(zefiro_std::Assert::assertEquals( (epected),(actual),__LINE__,__FILE__))

	/// �\���̃}�N��(�����]���A����)
#	define ZEFIRO_STD_ASSERT_DOUBLES	_EQUAL( expected , actual , delta )\
	(zefiro_std::Assert::assertEquals( expected , actual , delta , __LINE__ , __FILE__ ))

};	// namespace zefiro_std



#endif //__ASSERT_H__