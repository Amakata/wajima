#include <graphics/sys/Win32SpriteFactory.h>
#include <graphics/sys/Win32ImageSpriteImp.h>

namespace zefiro_graphics {
	Win32SpriteFactory::Win32SpriteFactory(){
	}
	ImageSpriteImp *Win32SpriteFactory::createImageSpriteImp(){
		return new Win32ImageSpriteImp();
	}
};
