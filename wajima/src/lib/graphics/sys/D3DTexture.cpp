#include "graphics/sys/D3DTexture.h"

namespace zefiro_graphics {
	D3DTexture::D3DTexture( LPDIRECT3DTEXTURE8 texture , D3DXIMAGE_INFO &info):texture_(texture),width_(info.Width),height_(info.Height){
		D3DSURFACE_DESC desc;
		texture_->GetLevelDesc( 0 , &desc );
		maxWidthRatio_ = (float)width_ / desc.Width;
		maxHeightRatio_ = (float)height_ / desc.Height;
	}
	D3DTexture::~D3DTexture(){
		texture_->Release();
		texture_ = NULL;
	}
};