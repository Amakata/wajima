/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/include/graphics/Attic/BaseSprite.h,v 1.3 2002/04/28 13:31:05 ama Exp $
 */

#ifndef __BASESPRITE_H__
#define __BASESPRITE_H__

#include <graphics/BaseSpriteImp.h>

namespace zefiro_graphics{
	/**
	 *	�x�[�X�X�v���C�g
	 *	�`��ʒu�������Ȃ��y�ʃX�v���C�g�ł���B
	 */
	class BaseSprite
	{
	public:
		/// �R���X�g���N�^
		/**
		 *	\param baseSpriteImp��BaseSprite����舵���X�v���C�g�̎����N���X�ւ̃|�C���^�ł���B
		 *	BaseSprite�N���X��baseSpriteImp��delete���s��Ȃ��BbaseSpriteImp��delete�̓��[�U�̐ӔC�ł���B
		 */
		BaseSprite( BaseSpriteImp *baseSpriteImp );
		///	�R�s�[�R���X�g���N�^
		/**
		 *	\param baseSprite�̓R�s�[����BaseSprite�N���X
		 *	BaseSprite�̐[���R�s�[���s���B
		 */
		BaseSprite( const BaseSprite &baseSprite );
		/// �f�X�g���N�^
		virtual ~BaseSprite();
		/// �`��
		/**
		 *	\param x�͉����̕`��ʒu�ł���B
		 *	\param y�͏c���̕`��ʒu�ł���B
		 *	\param srcBaseSprite�͕`�挳BaseSprite�ł���B
		 */
		virtual void render( const int x , const int y , const BaseSprite &srcBaseSprite ); 
		virtual int getWidth() const;
		virtual int getHeight() const;
		/// �F���̃r�b�g�[�x
		/**
		 *	\return �F���̃r�b�g�[�x�ł���B
		 *	�Ⴆ�΁A65536�F�̏ꍇ�A�F���̃r�b�g�[�x��16�ł���B
		 */
		virtual int getBitWidth() const;
		///	�����E�����������̃T�|�[�g����
		/**
		 *	\retval true �����E�������������T�|�[�g����Ă���B
		 *	\retval	false �����E�������������T�|�[�g����Ă��Ȃ��B
		 */
		virtual bool isTransparentable() const;
		/// �����E�����������̗L���̐ݒ�
		/**
		 *	\param transparent�͓����E�������������s�����B
		 *	<ul>
		 *	<li>true �����E�������������s���B</li>
		 *	<li>false �����E�������������s��Ȃ��B</li>
		 *	</ul>
		 */
		virtual void setTransparent( const bool transparent );
		///	�����E�����������̗L���̎擾
		/**
		 *	\retval true �����E�������������s���B
		 *	\retval false �����E�������������s��Ȃ��B
		 */
		virtual bool isTransparent() const;
		/// �`�揈���̗L���̐ݒ�
		/**
		 *	\param render�͕`�揈�����s�����B
		 */
		virtual void setRender( const bool render );
		/// �`�揈���̗L���̎擾
		/**
		 *	\retval true �`�揈�����s���B
		 *	\retval false �`�揈�����s��Ȃ��B
		 */
		virtual bool isRender() const;
		/// �`��t���[���̐ݒ�
		/**
		 *	\param number�͕`�悷��t���[���̔ԍ��ł���B
		 */
		virtual void setFrameNumber( const int number );
		///	�`��t���[���̎擾
		/**
		 *	\return �`�悷��t���[���̔ԍ��ł���B
		 */
		virtual int getFrameNumber() const;
		///	�`��t���[���̍ő�T�C�Y�̎擾
		/**
		 *	\return �`��t���[���̍ő�T�C�Y�ł���BgetMaxFrameSize()-1�܂�setFrameNumber�Őݒ�ł���B
		 */
		virtual int getMaxFrameSize() const;
	protected:
		BaseSpriteImp *_baseSpriteImp;	///< �X�v���C�g�̎����N���X
		bool _render;					///< �X�v���C�g�`�揈���̗L��
	};
};

#endif //__BASESPRITE_H__