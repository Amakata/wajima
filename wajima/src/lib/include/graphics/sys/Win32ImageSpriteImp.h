#ifndef __WIN32IMAGESPRITEIMP_H__
#define __WIN32IMAGESPRITEIMP_H__

#include <graphics/ImageSpriteImp.h>
#include <graphics/sys/Win32SpriteFactory.h>

namespace zefiro_graphics {
	class Win32ImageSpriteImp : public ImageSpriteImp
	{
	private:
		/// �R���X�g���N�^
		Win32ImageSpriteImp();
		friend zefiro_graphics::Win32SpriteFactory;
	public:
		/// �R�s�[�R���X�g���N�^
		/**
		 * \param win32ImageSpriteImp �R�s�[���X�v���C�g�̎����N���X
		 */
		Win32ImageSpriteImp( Win32ImageSpriteImp const &win32ImageSpriteImp );
		/// �f�X�g���N�^
		virtual ~Win32ImageSpriteImp();
		/// �`��
		/**
		 *	\param x�͉����̕`��ʒu�ł���B
		 *	\param y�͏c���̕`��ʒu�ł���B
		 *	\param srcBaseSpriteImp�͕`�挳BaseSpriteImp�ł���B
		 */
		virtual void render( int const x , int const y , BaseSpriteImp const *srcBaseSpriteImp );
		/// �X�v���C�g�̕��̎擾
		/**
		 * \return  �X�v���C�g�̕�
		 */
		virtual int getWidth() const;
		/// �X�v���C�g�̍����̎擾
		/**
		 * \return  �X�v���C�g�̍���
		 */
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
		 *	isTransparentable���������A�������̂ǂ�����T�|�[�g���邩��
		 *	�h���N���X�̎����ɂ���Ē�܂�B
		 */
		virtual void setTransparent( bool const transparent );
		///	�����E�����������̗L���̎擾
		/**
		 *	\retval true �����E�������������s���B
		 *	\retval false �����E�������������s��Ȃ��B
		 */
		virtual bool isTransparent() const;
		virtual void setFrameNumber( int const number );
		virtual int getFrameNumber() const;
		virtual int getMaxFrameSize() const;
	};
};

#endif //__WIN32IMAGESPRITEIMP_H__