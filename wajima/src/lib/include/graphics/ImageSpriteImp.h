#ifndef __IMAGESPRITEIMP_H__
#define __IMAGESPRITEIMP_H__
#include <graphics/BaseSpriteImp.h>

namespace zefiro_graphics
{
	class ImageSpriteImp : public BaseSpriteImp
	{
	public:
		ImageSpriteImp();
		ImageSpriteImp( ImageSpriteImp const &imageSpriteImp );
		virtual ~ImageSpriteImp();
	};
};


#endif //__IMAGESPRITEIMP_H__