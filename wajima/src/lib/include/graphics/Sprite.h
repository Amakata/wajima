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
		virtual void render( Sprite const &srcSprite );
		virtual void setPointX( int const x );
		virtual int getPointX() const;
		virtual void setPointY( int const y );
		virtual int getPointY() const;
		virtual void setPointZ( int const z );
		virtual int getPointZ() const;
	protected:
		int _pointX;	///< スプライトの位置
		int _pointY;	///< スプライトの位置
		int _pointZ;	///< スプライトの位置
	};
};

#endif //__SPRITE_H__