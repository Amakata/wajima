/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/include/lib/graphics/Attic/SpriteFactory.h,v 1.1 2002/05/10 19:28:41 ama Exp $
 */

#ifndef __SPRITEFACTORY_H__
#define __SPRITEFACTORY_H__

#include "graphics/ImageSpriteImp.h"

namespace zefiro_graphics {
	/**
	 * 抽象スプライトファクトリクラス
	 * スプライトの生成を一手に引き受けるクラスである。
	 */
	class SpriteFactory
	{
	public:
		// スプライトファクトリクラスの生成
		/**
		 * \return 生成したスプライトファクトリクラスへのポインタ。deleteはユーザの責任である。
		 */
		static SpriteFactory *createSpriteFactory();
		// ImageSpriteImpの生成
		/**
		 * \return 生成したスプライトへのポインタ。deleteはユーザの責任である。
		 */
		virtual ImageSpriteImp *createImageSpriteImp() =0;
	};
};

#endif //__SPRITEFACTORY_H__