#include <graphics/sys/D3D8.h>

namespace zefiro_graphics {
	D3D8::D3D8(){
		_pD3D = Direct3DCreate8( D3D_SDK_VERSION );
		if( NULL == _pD3D ){
			
		}
	}
	D3D8::~D3D8(){
		_pD3D->Release();
	}
};