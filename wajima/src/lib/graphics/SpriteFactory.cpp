#include <graphics/SpriteFactory.h>
#include <graphics/sys/Win32SpriteFactory.h>
namespace zefiro_graphics{
	SpriteFactory *SpriteFactory::createSpriteFactory(){
		return new Win32SpriteFactory();
	}
}