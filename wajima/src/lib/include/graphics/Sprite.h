/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/include/graphics/Attic/Sprite.h,v 1.3 2002/04/28 13:31:05 ama Exp $
 */

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
		virtual void render( const Sprite &srcSprite );
		virtual void setPointX( const int x );
		virtual int getPointX() const;
		virtual void setPointY( const int y );
		virtual int getPointY() const;
		virtual void setPointZ( const int z );
		virtual int getPointZ() const;
	protected:
		int _pointX;	///< �X�v���C�g�̈ʒu
		int _pointY;	///< �X�v���C�g�̈ʒu
		int _pointZ;	///< �X�v���C�g�̈ʒu
	};
};

#endif //__SPRITE_H__