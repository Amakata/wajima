/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/include/lib/graphics/sys/Attic/Win32SpriteFactory.h,v 1.1 2002/05/10 19:29:05 ama Exp $
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