/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/include/graphics/Attic/SpriteFactory.h,v 1.2 2002/04/28 13:31:05 ama Exp $
 */

#ifndef __SPRITEFACTORY_H__
#define __SPRITEFACTORY_H__

#include <graphics/ImageSpriteImp.h>

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