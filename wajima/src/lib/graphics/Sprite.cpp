/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/graphics/Attic/Sprite.cpp,v 1.4 2002/04/29 16:24:34 ama Exp $
 */

#include "graphics/Sprite.h"

namespace zefiro_graphics {
	Sprite::Sprite( BaseSpriteImp *baseSpriteImp )
		:_pointX(0),_pointY(0),BaseSprite(baseSpriteImp){
	};
	Sprite::~Sprite(){
	}
	void Sprite::render( const Sprite &srcSprite ){
		BaseSprite::render( srcSprite._pointX , srcSprite._pointY , srcSprite );
	}
	void Sprite::setPointX( const int x ){
			_pointX = x;
	}
	int Sprite::getPointX() const{
			return _pointX;
	}
	void Sprite::setPointY( const int y ){
			_pointY = y;
	}
	int Sprite::getPointY() const{
			return _pointY;
	}
	void Sprite::setPointZ( const int z ){
			_pointZ = z;
	}
	int Sprite::getPointZ() const{
			return _pointZ;
	}
};