/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/include/lib/graphics/sys/Attic/D3DDevice.h,v 1.4 2002/09/19 11:00:55 ama Exp $
 */
#ifndef __D3DDEVICE8_H__
#define __D3DDEVICE8_H__

#include <d3d8.h>
#include <d3dx8core.h>
#include <string>

#include "graphics/sys/D3DTexture.h"
#include "graphics/sys/D3DFont.h"


namespace zefiro_graphics {
	class D3DDevice{
	public:
		D3DDevice( LPDIRECT3DDEVICE8 d3ddevice8 );
		virtual ~D3DDevice();
		D3DTexture *loadTexture( const std::string filename ) const;
		D3DFont *createFont( const int width , const int height , std::string fontname );
		void renderBegin();
		void renderEnd();
		void render( const D3DTexture *texture , const float x , const float y , const float z );
		void clear();
	protected:
		LPDIRECT3DDEVICE8	d3dDevice8_;
		
	};
};

#endif //__D3DDEVICE8_H__