/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/include/graphics/Attic/ImageSpriteImp.h,v 1.4 2002/04/29 16:27:34 ama Exp $
 */

#ifndef __IMAGESPRITEIMP_H__
#define __IMAGESPRITEIMP_H__
#include "graphics/BaseSpriteImp.h"

namespace zefiro_graphics
{
	class ImageSpriteImp : public BaseSpriteImp
	{
	public:
		ImageSpriteImp();
		ImageSpriteImp( const ImageSpriteImp &imageSpriteImp );
		virtual ~ImageSpriteImp();
	};
};


#endif //__IMAGESPRITEIMP_H__