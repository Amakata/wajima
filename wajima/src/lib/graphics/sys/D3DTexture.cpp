#include "graphics/sys/D3DTexture.h"

namespace zefiro_graphics {
	D3DTexture::D3DTexture( LPDIRECT3DTEXTURE8 texture ):texture_(texture){
	}
	D3DTexture::~D3DTexture(){
		texture_->Release();
	}
};