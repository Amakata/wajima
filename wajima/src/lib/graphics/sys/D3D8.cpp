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
	std::vector<Adapter> D3D8::getAdapterVector() const{
		ZEFIRO_STD_ASSERT( isAvailable() );
		std::vector<Adapter> result;
		for( int adapterid = 0 ; adapterid < getAdapterCount() ; ++adapterid ){				
			Adapter adapter = Adapter( adapterid , getAdapterIdentifier( adapterid ) );
			for( int modeid = 0 ; modeid < getAdapterModeCount(adapterid) ; ++modeid ){
				adapter.addMode( getAdapterMode( adapterid , modeid ) );
			}
			result.push_back( adapter );
		}
		return result;
	}
	Mode D3D8::getAdapterMode( const int adapterid , const int modeid ) const{
		ZEFIRO_STD_ASSERT( isAvailable() );
		
		D3DDISPLAYMODE d3dDisplayMode ;
		HRESULT hr = _pD3D->EnumAdapterModes( adapterid , modeid , &d3dDisplayMode );
		if( hr == D3DERR_INVALIDCALL ){
		}
		return Mode( modeid , d3dDisplayMode.Width , d3dDisplayMode.Height , d3dDisplayMode.RefreshRate , d3dDisplayMode.Format );
	}
	std::string D3D8::getAdapterIdentifier( const int adapterid ) const{
		ZEFIRO_STD_ASSERT( isAvailable() );

		D3DADAPTER_IDENTIFIER8	d3dAdapterIdentifier;
		HRESULT hr = _pD3D->GetAdapterIdentifier( adapterid , D3DENUM_NO_WHQL_LEVEL , & d3dAdapterIdentifier );
		if( hr == D3DERR_INVALIDCALL ){
		}
		return std::string( d3dAdapterIdentifier.Description );
	}
};