/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/include/graphics/Attic/ImageSpriteImp.h,v 1.3 2002/04/28 13:31:05 ama Exp $
 */

#ifndef __IMAGESPRITEIMP_H__
#define __IMAGESPRITEIMP_H__
#include <graphics/BaseSpriteImp.h>

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