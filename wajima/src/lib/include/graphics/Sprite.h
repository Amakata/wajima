#ifndef __SPRITE_H__
#define __SPRITE_H__
#include <graphics/BaseSprite.h>

namespace zefiro_graphics {
	/**
	 *	�X�X�v���C�g
	 *	�`��ʒu���������X�v���C�g�ł���B
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
		int _pointX;	///< �X�v���C�g�̈ʒu
		int _pointY;	///< �X�v���C�g�̈ʒu
		int _pointZ;	///< �X�v���C�g�̈ʒu
	};
};

#endif //__SPRITE_H__