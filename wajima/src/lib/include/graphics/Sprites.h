#ifndef __SPRITES_H__
#define __SPRITES_H__

#include <vector>
#include <std/countptr.h>
#include <graphics/Sprite.h>
#include <graphics/Sprites.h>

namespace zefiro_graphics{
	class Sprites : public Sprite
	{
	public:
		Sprites( BaseSpriteImp *baseSpriteImp );
		virtual ~Sprites();
		virtual void render();
		virtual void addSprite( zefiro_std::count_ptr<Sprite> sprite );
		virtual void deleteSprite( zefiro_std::count_ptr<Sprite> sprite );
	protected:
		std::vector<zefiro_std::count_ptr<Sprite> >	_sprites;
	};
};

#endif //__SPRITES_H__