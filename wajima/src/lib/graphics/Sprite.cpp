#include <graphics/Sprite.h>

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