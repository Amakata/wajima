/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/include/lib/graphics/Attic/ImageSpriteImp.h,v 1.1 2002/05/10 19:28:41 ama Exp $
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