#ifndef __D3DTEXTURE_H__
#define __D3DTEXTURE_H__

#include <string>
#include <d3d8.h>

namespace zefiro_graphics {
	class D3DDevice;
	class D3DTexture{
		friend D3DDevice;
	public:
		D3DTexture( LPDIRECT3DTEXTURE8 texture );
		virtual ~D3DTexture();
	protected:
		LPDIRECT3DTEXTURE8 texture_;
	};
};

#endif // __D3DTEXTURE_H__