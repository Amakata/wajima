/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/graphics/Attic/SpriteFactory.cpp,v 1.3 2002/04/29 16:24:34 ama Exp $
 */

#include "graphics/SpriteFactory.h"
#include "graphics/sys/Win32SpriteFactory.h"

namespace zefiro_graphics{
	SpriteFactory *SpriteFactory::createSpriteFactory(){
		return new Win32SpriteFactory();
	}
}