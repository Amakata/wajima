#ifndef __D3DTEXTURE_H__
#define __D3DTEXTURE_H__

#include <string>
#include <d3d8.h>
#include <d3dx8mesh.h>

namespace zefiro_graphics {
	class D3DDevice;
	class D3DTexture{
		friend D3DDevice;
	public:
		D3DTexture( LPDIRECT3DTEXTURE8 texture , D3DXIMAGE_INFO &info );
		virtual ~D3DTexture();
		int getWidth()const;
		int getHeight()const;
	protected:
		LPDIRECT3DTEXTURE8 texture_;
		int width_;
		int height_;
	};
};

#endif // __D3DTEXTURE_H__