/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/graphics/Attic/BaseSprite.cpp,v 1.4 2002/04/29 16:24:34 ama Exp $
 */

#include "graphics/BaseSprite.h"

namespace zefiro_graphics {
	BaseSprite::BaseSprite( BaseSpriteImp *baseSpriteImp ):_baseSpriteImp(baseSpriteImp),_render(true){
	}
	BaseSprite::BaseSprite( const BaseSprite &baseSprite ){
	}
	BaseSprite::~BaseSprite(){
	}
	void BaseSprite::render(  const int x , const int y , const BaseSprite &srcBaseSprite ){
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
	void BaseSprite::setTransparent( const bool transparent ){
		_baseSpriteImp->setTransparent( transparent );
	}
	bool BaseSprite::isTransparent() const{
		return _baseSpriteImp->isTransparent();
	}
	void BaseSprite::setRender( const bool render ){
		_render = render;
	}
	bool BaseSprite::isRender() const{
		return _render;
	}
	void BaseSprite::setFrameNumber( const int number ){
		_baseSpriteImp->setFrameNumber( number );
	}
	int BaseSprite::getFrameNumber() const{
		return _baseSpriteImp->getFrameNumber();
	}
	int BaseSprite::getMaxFrameSize() const{
		return _baseSpriteImp->getMaxFrameSize();
	}
};