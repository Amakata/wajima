/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/graphics/sys/Attic/D3D8.cpp,v 1.12 2002/09/18 14:45:37 ama Exp $
 */

#include "std/Assert.h"

#include "graphics/sys/D3D8.h"
#include "graphics/sys/DXAssert.h"


namespace zefiro_graphics {
	D3D8::D3D8(){
		d3d_ = Direct3DCreate8( D3D_SDK_VERSION );
	}
	D3D8::~D3D8(){
		if( isAvailable() ){
			d3d_->Release();
			d3d_ = NULL;
		}
	}
	int D3D8::getAdapterCount() const{
		ZEFIRO_STD_ASSERT( isAvailable() );
		return d3d_->GetAdapterCount();
	}
	int D3D8::getAdapterModeCount( const int adapter ) const{
		ZEFIRO_STD_ASSERT( isAvailable() );
		return d3d_->GetAdapterModeCount( adapter );
	}
	bool D3D8::isAvailable() const{
		return d3d_ != NULL;
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
		param.AutoDepthStencilFormat = D3DFMT_D16;
		LPDIRECT3DDEVICE8 d3dDevice;
		DWORD behaviorFlags = NULL;
		if( threaded ){
			behaviorFlags = D3DCREATE_MULTITHREADED;
		}
		HRESULT hr;
		hr = d3d_->CreateDevice( adapterid , D3DDEVTYPE_HAL  , hwnd  ,D3DCREATE_HARDWARE_VERTEXPROCESSING | behaviorFlags ,&param , &d3dDevice );
		if( D3D_OK != hr  ){
			hr = d3d_->CreateDevice( adapterid , D3DDEVTYPE_HAL , hwnd , D3DCREATE_SOFTWARE_VERTEXPROCESSING | behaviorFlags, &param , &d3dDevice );
		}
		if( D3D_OK != hr ){
			hr = d3d_->CreateDevice( adapterid , D3DDEVTYPE_REF , hwnd , D3DCREATE_HARDWARE_VERTEXPROCESSING | behaviorFlags , &param , &d3dDevice );
		}
		if( D3D_OK != hr ){
			hr = d3d_->CreateDevice( adapterid , D3DDEVTYPE_REF , hwnd , D3DCREATE_SOFTWARE_VERTEXPROCESSING | behaviorFlags , &param , &d3dDevice );
		}
		DXASSERT( hr );
		return new D3DDevice(d3dDevice);
	}
	Mode D3D8::getAdapterMode( const int adapterid , const int modeid ) const{
		ZEFIRO_STD_ASSERT( isAvailable() );
		
		D3DDISPLAYMODE d3dDisplayMode ;
		HRESULT hr = d3d_->EnumAdapterModes( adapterid , modeid , &d3dDisplayMode );
		DXASSERT( hr );
		return Mode(  d3dDisplayMode.Width , d3dDisplayMode.Height , d3dDisplayMode.RefreshRate , d3dDisplayMode.Format );
	}
	std::string D3D8::getAdapterIdentifier( const int adapterid ) const{
		ZEFIRO_STD_ASSERT( isAvailable() );

		D3DADAPTER_IDENTIFIER8	d3dAdapterIdentifier;
		HRESULT hr = d3d_->GetAdapterIdentifier( adapterid , D3DENUM_NO_WHQL_LEVEL , & d3dAdapterIdentifier );
		DXASSERT( hr );
		return std::string( d3dAdapterIdentifier.Description );
	}
};