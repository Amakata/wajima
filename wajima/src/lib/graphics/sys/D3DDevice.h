/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/graphics/sys/Attic/D3DDevice.h,v 1.1 2002/11/03 09:04:44 ama Exp $
 */
#ifndef __D3DDEVICE8_H__
#define __D3DDEVICE8_H__

#include <d3d8.h>
#include <d3dx8core.h>
#include <string>
#include <map>
#include <vector>

#include "graphics/sys/D3DTexture.h"
#include "graphics/sys/D3DFont.h"


namespace zefiro_graphics {
	class D3DDevice{
	public:
		D3DDevice( LPDIRECT3DDEVICE8 d3ddevice8 );
		virtual ~D3DDevice();
		D3DTexture *loadTexture( const std::string filename ) const;
		D3DFont *createFont( const int width , const int height , std::string fontname );
		void clear();
		void render();
		void setBegin();
		void setSprite( const D3DTexture *texture , const float x , const float y , const float z , const bool transparent );
		void setEnd();
		void present();
	protected:
		void getDeviceCapability();
		void setDefaultRenderState();
		void setDefaultTextureStageState();

		typedef D3DTexture* LPD3DTEXTURE;
		typedef std::map< LPD3DTEXTURE , std::vector<D3DXVECTOR3> > SPRITE_CONTAINER;

		LPDIRECT3DDEVICE8	device_;
		D3DCAPS8 caps_;

		SPRITE_CONTAINER	sprites_;
		SPRITE_CONTAINER	transparentSprites_;
		LPDIRECT3DVERTEXBUFFER8	vbOfSprites_;
		LPDIRECT3DVERTEXBUFFER8	vbOfTransparentSprites_;
		int					numOfSprite_;
		int					numOfTransparentSprite_;
	};
};

#endif //__D3DDEVICE8_H__