#include <graphics/Sprite.h>

namespace zefiro_graphics {
	Sprite::Sprite( BaseSpriteImp *baseSpriteImp )
		:_pointX(0),_pointY(0),BaseSprite(baseSpriteImp){
	};
	Sprite::~Sprite(){
	}
	void Sprite::render( Sprite const &srcSprite ){
		BaseSprite::render( srcSprite._pointX , srcSprite._pointY , srcSprite );
	}
	void Sprite::setPointX( int const x ){
			_pointX = x;
	}
	int Sprite::getPointX() const{
			return _pointX;
	}
	void Sprite::setPointY( int const y ){
			_pointY = y;
	}
	int Sprite::getPointY() const{
			return _pointY;
	}
	void Sprite::setPointZ( int const z ){
			_pointZ = z;
	}
	int Sprite::getPointZ() const{
			return _pointZ;
	}
};