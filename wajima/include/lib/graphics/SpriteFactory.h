/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/include/lib/graphics/Attic/SpriteFactory.h,v 1.1 2002/05/10 19:28:41 ama Exp $
 */

#ifndef __SPRITEFACTORY_H__
#define __SPRITEFACTORY_H__

#include "graphics/ImageSpriteImp.h"

namespace zefiro_graphics {
	/**
	 * ���ۃX�v���C�g�t�@�N�g���N���X
	 * �X�v���C�g�̐��������Ɉ����󂯂�N���X�ł���B
	 */
	class SpriteFactory
	{
	public:
		// �X�v���C�g�t�@�N�g���N���X�̐���
		/**
		 * \return ���������X�v���C�g�t�@�N�g���N���X�ւ̃|�C���^�Bdelete�̓��[�U�̐ӔC�ł���B
		 */
		static SpriteFactory *createSpriteFactory();
		// ImageSpriteImp�̐���
		/**
		 * \return ���������X�v���C�g�ւ̃|�C���^�Bdelete�̓��[�U�̐ӔC�ł���B
		 */
		virtual ImageSpriteImp *createImageSpriteImp() =0;
	};
};

#endif //__SPRITEFACTORY_H__