/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/include/graphics/Attic/Sprite.h,v 1.3 2002/04/28 13:31:05 ama Exp $
 */

#ifndef __SPRITE_H__
#define __SPRITE_H__
#include <graphics/BaseSprite.h>

namespace zefiro_graphics {
	/**
	 *	ススプライト
	 *	描画位置を持ったスプライトである。
	 */
	class Sprite : public BaseSprite
	{
	public:
		Sprite( BaseSpriteImp *baseSpriteImp );
		virtual ~Sprite();
		virtual void render( const Sprite &srcSprite );
		virtual void setPointX( const int x );
		virtual int getPointX() const;
		virtual void setPointY( const int y );
		virtual int getPointY() const;
		virtual void setPointZ( const int z );
		virtual int getPointZ() const;
	protected:
		int _pointX;	///< スプライトの位置
		int _pointY;	///< スプライトの位置
		int _pointZ;	///< スプライトの位置
	};
};

#endif //__SPRITE_H__