/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/include/lib/graphics/sys/Attic/D3DDevice.h,v 1.2 2002/09/13 05:34:44 ama Exp $
 */
#ifndef __D3DDEVICE8_H__
#define __D3DDEVICE8_H__

#include <d3d8.h>
#include <d3dx8core.h>
#include <string>

#include "graphics/sys/D3DTexture.h"

namespace zefiro_graphics {
	class D3DDevice{
	public:
		D3DDevice( LPDIRECT3DDEVICE8 d3ddevice8 , LPD3DXSPRITE d3dsprite );
		virtual ~D3DDevice();
		D3DTexture *loadTexture( const std::string filename ) const;
		void renderBegin();
		void renderEnd();
		void render( const D3DTexture *texture , float x ,float , float z );
		void clear();
	protected:
		LPDIRECT3DDEVICE8	D3DDevice8_;
		LPD3DXSPRITE	D3DSprite_;
	};
};

#endif //__D3DDEVICE8_H__