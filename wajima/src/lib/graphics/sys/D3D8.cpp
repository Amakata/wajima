/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/graphics/sys/Attic/D3D8.cpp,v 1.10 2002/08/25 12:07:45 ama Exp $
 */

#include "std/Assert.h"

#include "graphics/sys/D3D8.h"
#include "graphics/sys/DXAssert.h"


namespace zefiro_graphics {
	D3D8::D3D8(){
		pD3D_ = Direct3DCreate8( D3D_SDK_VERSION );
	}
	D3D8::~D3D8(){
		if( isAvailable() ){
			pD3D_->Release();
		}
	}
	int D3D8::getAdapterCount() const{
		ZEFIRO_STD_ASSERT( isAvailable() );
		return pD3D_->GetAdapterCount();
	}
	int D3D8::getAdapterModeCount( const int adapter ) const{
		ZEFIRO_STD_ASSERT( isAvailable() );
		return pD3D_->GetAdapterModeCount( adapter );
	}
	bool D3D8::isAvailable() const{
		return pD3D_ != NULL;
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
	D3DDevice* D3D8::createDevice( const int adapterid , Mode &mode , bool windowed , bool threaded , HWND hwnd ) const{


		D3DPRESENT_PARAMETERS param;
		memset( &param , 0 , sizeof(param) );	
		param.BackBufferWidth = mode.getWidth();
		param.BackBufferHeight = mode.getHeight();
		param.BackBufferFormat = mode.getFormat();
		param.BackBufferCount = 1;
		param.SwapEffect = D3DSWAPEFFECT_DISCARD;
		param.Windowed = windowed;
		param.EnableAutoDepthStencil = TRUE;
		param.AutoDepthStencilFormat = D3DFMT_D16;	//	
		LPDIRECT3DDEVICE8 pD3DDevice;
		DWORD behaviorFlags = NULL;
		if( threaded ){
			behaviorFlags = D3DCREATE_MULTITHREADED;
		}

		HRESULT hr;
		hr = pD3D_->CreateDevice( adapterid , D3DDEVTYPE_HAL  , hwnd  ,D3DCREATE_HARDWARE_VERTEXPROCESSING | behaviorFlags ,&param , &pD3DDevice );
		if( D3D_OK != hr  ){
			hr = pD3D_->CreateDevice( adapterid , D3DDEVTYPE_HAL , hwnd , D3DCREATE_SOFTWARE_VERTEXPROCESSING | behaviorFlags, &param , &pD3DDevice );
		}
		if( D3D_OK != hr ){
			hr = pD3D_->CreateDevice( adapterid , D3DDEVTYPE_REF , hwnd , D3DCREATE_HARDWARE_VERTEXPROCESSING | behaviorFlags , &param , &pD3DDevice );
		}
		if( D3D_OK != hr ){
			hr = pD3D_->CreateDevice( adapterid , D3DDEVTYPE_REF , hwnd , D3DCREATE_SOFTWARE_VERTEXPROCESSING | behaviorFlags , &param , &pD3DDevice );
		}
		DXASSERT( hr );
		return new D3DDevice(pD3DDevice);
	}
	Mode D3D8::getAdapterMode( const int adapterid , const int modeid ) const{
		ZEFIRO_STD_ASSERT( isAvailable() );
		
		D3DDISPLAYMODE d3dDisplayMode ;
		HRESULT hr = pD3D_->EnumAdapterModes( adapterid , modeid , &d3dDisplayMode );
		DXASSERT( hr );
		return Mode(  d3dDisplayMode.Width , d3dDisplayMode.Height , d3dDisplayMode.RefreshRate , d3dDisplayMode.Format );
	}
	std::string D3D8::getAdapterIdentifier( const int adapterid ) const{
		ZEFIRO_STD_ASSERT( isAvailable() );

		D3DADAPTER_IDENTIFIER8	d3dAdapterIdentifier;
		HRESULT hr = pD3D_->GetAdapterIdentifier( adapterid , D3DENUM_NO_WHQL_LEVEL , & d3dAdapterIdentifier );
		DXASSERT( hr );
		return std::string( d3dAdapterIdentifier.Description );
	}
};