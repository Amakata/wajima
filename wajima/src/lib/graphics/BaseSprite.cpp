#include <graphics/BaseSprite.h>

namespace zefiro_graphics {
	BaseSprite::BaseSprite( BaseSpriteImp *baseSpriteImp ):_baseSpriteImp(baseSpriteImp),_render(true){
	}
	BaseSprite::BaseSprite( BaseSprite const &baseSprite ){
	}
	BaseSprite::~BaseSprite(){
	}
	void BaseSprite::render( int const x , int const y , BaseSprite const &srcBaseSprite ){
		if( _render ){
			_baseSpriteImp->render( x , y , srcBaseSprite._baseSpriteImp );
		}
	}
	int BaseSprite::getWidth() const{
		return _baseSpriteImp->getWidth();
	}
	int BaseSprite::getHeight() const{
		return _baseSpriteImp->getHeight();
	}
	int BaseSprite::getBitWidth() const{
		return _baseSpriteImp->getBitWidth();
	}
	bool BaseSprite::isTransparentable() const{
		return _baseSpriteImp->isTransparentable();
	}
	void BaseSprite::setTransparent( bool const transparent ){
		_baseSpriteImp->setTransparent( transparent );
	}
	bool BaseSprite::isTransparent() const{
		return _baseSpriteImp->isTransparent();
	}
	void BaseSprite::setRender( bool const render ){
		_render = render;
	}
	bool BaseSprite::isRender() const{
		return _render;
	}
	void BaseSprite::setFrameNumber( int const number ){
		_baseSpriteImp->setFrameNumber( number );
	}
	int BaseSprite::getFrameNumber() const{
		return _baseSpriteImp->getFrameNumber();
	}
	int BaseSprite::getMaxFrameSize() const{
		return _baseSpriteImp->getMaxFrameSize();
	}
};