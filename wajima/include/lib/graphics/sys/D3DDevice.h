/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/include/lib/graphics/sys/Attic/D3DDevice.h,v 1.1 2002/08/13 06:47:23 ama Exp $
 */
#ifndef __D3DDEVICE8_H__
#define __D3DDEVICE8_H__

#include <d3d8.h>

namespace zefiro_graphics {
	class D3DDevice{
	public:
		D3DDevice( LPDIRECT3DDEVICE8 d3ddevice8 );
		virtual ~D3DDevice();

	protected:
		LPDIRECT3DDEVICE8	pD3DDevice8_;
	};
};

#endif //__D3DDEVICE8_H__