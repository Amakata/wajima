/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/graphics/sys/Attic/Win32SpriteFactory.cpp,v 1.2 2002/04/28 13:32:49 ama Exp $
 */

#include <graphics/sys/Win32SpriteFactory.h>
#include <graphics/sys/Win32ImageSpriteImp.h>

namespace zefiro_graphics {
	Win32SpriteFactory::Win32SpriteFactory(){
	}
	ImageSpriteImp *Win32SpriteFactory::createImageSpriteImp(){
		return new Win32ImageSpriteImp();
	}
};
