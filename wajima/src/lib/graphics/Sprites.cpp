#include <graphics/Sprites.h>

namespace zefiro_graphics{
	Sprites::Sprites( BaseSpriteImp *baseSpriteImp ):Sprite(baseSpriteImp){
	}
	Sprites::~Sprites(){
	}
	void Sprites::render(){
		if( _render ){
			std::vector< zefiro_std::count_ptr<Sprite> >::iterator	sprites;
			for( sprites = _sprites.begin() ; sprites < _sprites.end() ; ++sprites ){
				Sprite::render(  **sprites );
			}
		}
	}
	void Sprites::addSprite( zefiro_std::count_ptr<Sprite> sprite ){
		_sprites.push_back( sprite );
	}
	void Sprites::deleteSprite( zefiro_std::count_ptr<Sprite> sprite ){
		
	}
};