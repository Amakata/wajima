/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/graphics/GraphicsDevice.h,v 1.2 2002/11/14 16:51:06 ama Exp $
 */

#ifndef __GRAPHICSDEVICE_H__
#define __GRAPHICSDEVICE_H__

namespace zefiro_graphics {
	class GraphicsDevice {
	public:
		GraphicsDevice( LPDIRECT3D8 d3d8 , int , int , int , bool );
	};
};
#endif //__GRAPHICSDEVICE_H__