/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/include/graphics/sys/Attic/Win32SpriteFactory.h,v 1.3 2002/04/29 16:28:02 ama Exp $
 */

#ifndef __WIN32SPRITEFACTORY_H__
#define __WIN32SPRITEFACTORY_H__

#include "graphics/SpriteFactory.h"

namespace zefiro_graphics {
	class Win32SpriteFactory: public SpriteFactory {
	private:
		Win32SpriteFactory();
		friend zefiro_graphics::SpriteFactory;
	public:
		ImageSpriteImp *createImageSpriteImp();
	};
};

#endif //__WIN32SPRITEFACTORY_H__