#include "graphics/sys/D3DTexture.h"

namespace zefiro_graphics {
	D3DTexture::D3DTexture( LPDIRECT3DTEXTURE8 texture , D3DXIMAGE_INFO &info):texture_(texture),width_(info.Width),height_(info.Height){
		D3DSURFACE_DESC desc;
		texture_->GetLevelDesc( 0 , &desc );
		memset( cv , 0 , sizeof CUSTOMVERTEX * 6 );
		float heightRatio = (height_ + 0.5f )/ desc.Height;
		float widthRatio = (width_ + 0.5f ) / desc.Width;;
												cv[0].rhw = 1.0f;
		cv[1].x = width_;	cv[1].y = height_;	cv[1].rhw = 1.0f;	cv[1].tu = widthRatio;	cv[1].tv = heightRatio;
							cv[2].y = height_;	cv[2].rhw = 1.0f;							cv[2].tv = heightRatio;
		cv[3].x = width_;						cv[3].rhw = 1.0f;	cv[3].tu = widthRatio;
		cv[4] = cv[1];
												cv[5].rhw = 1.0f;
	}
	D3DTexture::~D3DTexture(){
		texture_->Release();
		texture_ = NULL;
	}
};