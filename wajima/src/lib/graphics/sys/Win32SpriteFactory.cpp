/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/graphics/sys/Attic/Win32SpriteFactory.cpp,v 1.3 2002/04/29 16:25:41 ama Exp $
 */

#include "graphics/sys/Win32SpriteFactory.h"
#include "graphics/sys/Win32ImageSpriteImp.h"

namespace zefiro_graphics {
	Win32SpriteFactory::Win32SpriteFactory(){
	}
	ImageSpriteImp *Win32SpriteFactory::createImageSpriteImp(){
		return new Win32ImageSpriteImp();
	}
};
