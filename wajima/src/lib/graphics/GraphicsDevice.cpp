/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/graphics/GraphicsDevice.cpp,v 1.1 2002/12/13 19:53:33 ama Exp $
 */

#include "GraphicsDevice.h"

namespace zefiro_graphics {
	GraphicsDevice::GraphicsDevice(
		LPDIRECT3DDEVICE8 device ,
		int width , int height , 
		ColorFormat front ,	ColorFormat back , DepthFormat depth , 
		int refreshRate , bool windowed )
		:device_(device),width_(width),height_(height),
		front_(front),back_(back),depth_(depth),
		refreshRate_(refreshRate),windowed_(windowed){
	}
};