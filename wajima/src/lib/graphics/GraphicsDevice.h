/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/graphics/GraphicsDevice.h,v 1.4 2002/12/13 19:53:33 ama Exp $
 */

#ifndef __GRAPHICSDEVICE_H__
#define __GRAPHICSDEVICE_H__

#include <d3d8.h>

#include "SmartPtr.h"
#include "ColorFormat.h"
#include "DepthFormat.h"

namespace zefiro_graphics {
	class GraphicsDevice {
	public:
		typedef Loki::SmartPtr<GraphicsDevice> GD;
	protected:
		GraphicsDevice( LPDIRECT3DDEVICE8 device , int width , int height , ColorFormat front , ColorFormat back , DepthFormat depth , int refreshRate , bool windowed );
	private:
		int width_;
		int height_;
		int refreshRate_;
		bool windowed_;
		ColorFormat front_;
		ColorFormat back_;
		DepthFormat depth_;
		LPDIRECT3DDEVICE8 device_;
		GraphicsDevice();
		GraphicsDevice( const GraphicsDevice & );
		GraphicsDevice& operator=( const GraphicsDevice & );
	};
};
#endif //__GRAPHICSDEVICE_H__