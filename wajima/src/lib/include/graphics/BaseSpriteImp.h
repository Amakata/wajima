/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/include/graphics/Attic/BaseSpriteImp.h,v 1.4 2002/04/29 16:27:34 ama Exp $
 */

#ifndef __BASESPRITEIMP_H__
#define __BASESPRITEIMP_H__

namespace zefiro_graphics{
	/**
	 * �X�v���C�g�̎����N���X�̉��z���N���X
	 * �ʒu���w�肵���X�v���C�g�̎����N���X���m�̕`���A
	 * �X�v���C�g�̑傫���A�F�A�����A�t���[�����̎�舵�����\�ł���B
	 */
	class BaseSpriteImp {
	public:
		/// �R���X�g���N�^
		/**
		 *	���z���N���X�ł���A�Ȃɂ����Ȃ��B
		 */
		BaseSpriteImp();
		/// �R�s�[�R���X�g���N�^
		/**
		 *	���z���N���X�ł���A�Ȃɂ����Ȃ��B
		 */
		BaseSpriteImp( const BaseSpriteImp &baseSpriteImp );
		/// �f�X�g���N�^
		/**
		 *	���z���N���X�ł���A�Ȃɂ����Ȃ��B
		 * \param baseSpriteImp �R�s�[���X�v���C�g�̎����N���X
		 */
		virtual ~BaseSpriteImp();
		/// �`��
		/**
		 *	\param x�͉����̕`��ʒu�ł���B
		 *	\param y�͏c���̕`��ʒu�ł���B
		 *	\param srcBaseSpriteImp�͕`�挳BaseSpriteImp�ł���B
		 */
		virtual void render( const int x , const int y , const BaseSpriteImp *srcBaseSpriteImp )=0;
		/// �X�v���C�g�̕��̎擾
		/**
		 * \return  �X�v���C�g�̕�
		 */
		virtual int getWidth() const =0;
		/// �X�v���C�g�̍����̎擾
		/**
		 * \return  �X�v���C�g�̍���
		 */
		virtual int getHeight() const =0;
		/// �F���̃r�b�g�[�x
		/**
		 *	\return �F���̃r�b�g�[�x�ł���B
		 *	�Ⴆ�΁A65536�F�̏ꍇ�A�F���̃r�b�g�[�x��16�ł���B
		 */
		virtual int getBitWidth() const =0;
		///	�����E�����������̃T�|�[�g����
		/**
		 *	\retval true �����E�������������T�|�[�g����Ă���B
		 *	\retval	false �����E�������������T�|�[�g����Ă��Ȃ��B
		 */
		virtual bool isTransparentable() const =0;
		/// �����E�����������̗L���̐ݒ�
		/**
		 *	\param transparent�͓����E�������������s�����B
		 *	<ul>
		 *	<li>true �����E�������������s���B</li>
		 *	<li>false �����E�������������s��Ȃ��B</li>
		 *	</ul>
		 *	isTransparentable���������A�������̂ǂ�����T�|�[�g���邩��
		 *	�h���N���X�̎����ɂ���Ē�܂�B
		 */
		virtual void setTransparent( const bool transparent ) =0;
		///	�����E�����������̗L���̎擾
		/**
		 *	\retval true �����E�������������s���B
		 *	\retval false �����E�������������s��Ȃ��B
		 */
		virtual bool isTransparent() const =0;
		virtual void setFrameNumber( const int number ) =0;
		virtual int getFrameNumber() const =0;
		virtual int getMaxFrameSize() const =0;
	};
};
#endif //__BASESPRITEIMP_H__