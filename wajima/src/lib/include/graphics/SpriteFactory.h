/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/include/graphics/Attic/SpriteFactory.h,v 1.3 2002/04/29 16:27:33 ama Exp $
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