#ifndef __GRAPHICSDEVICE_H__
#define __GRAPHICSDEVICE_H__
/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/graphics/GraphicsDevice.h,v 1.1 2002/11/13 18:28:08 ama Exp $
 */

namespace zefiro_graphics {
	class GraphicsDevice {
	public:
		GraphicsDevice( LPDIRECT3D8 d3d8 , int , int , int , bool );
	};
};
#endif //__GRAPHICSDEVICE_H__