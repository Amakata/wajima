#include <graphics/sys/D3D8.h>
#include <std/Assert.h>
namespace zefiro_graphics {
	D3D8::D3D8(){
		_pD3D = Direct3DCreate8( D3D_SDK_VERSION );
	}
	D3D8::~D3D8(){
		if( isAvailable() ){
			_pD3D->Release();
		}
	}
	int D3D8::getAdapterCount() const{
		ZEFIRO_STD_ASSERT( isAvailable() );
		return _pD3D->GetAdapterCount();
	}
	int D3D8::getAdapterModeCount( const int adapter ) const{
		ZEFIRO_STD_ASSERT( isAvailable() );
		return _pD3D->GetAdapterModeCount( adapter );
	}
	bool D3D8::isAvailable() const{
		return _pD3D != NULL;
	}
};