/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/graphics/GraphicsDevice.h,v 1.3 2002/11/24 14:54:21 ama Exp $
 */

#ifndef __GRAPHICSDEVICE_H__
#define __GRAPHICSDEVICE_H__

#include "SmartPtr.h"
#include "ColorFormat.h"

namespace zefiro_graphics {
	class GraphicsDevice {
	public:
		typedef Loki::SmartPtr<GraphicsDevice> GD;
		GraphicsDevice( int width , int height , ColorFormat colorFormat , int refreshRate , bool windowed );
	};
};
#endif //__GRAPHICSDEVICE_H__