/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/graphics/GraphicsDevice.cpp,v 1.4 2002/12/15 10:52:26 ama Exp $
 */

#include "GraphicsDevice.h"
#include "sys/DXAssert.h"

namespace zefiro_graphics {
	GraphicsDevice::GraphicsDevice( LPDIRECT3DDEVICE8 device ):device_(device){
	}
	GraphicsDevice::~GraphicsDevice(){
		device_->Release();
	}
	void GraphicsDevice::clear( Color& color , float depth ){
		if( HRESULT hr = device_->Clear( 0 , NULL , D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER  , color.getColor() , depth , 0 )!=D3D_OK ){
			DXASSERT( hr );
		}
	}
	void GraphicsDevice::present(){
		if( HRESULT hr = device_->Present( NULL , NULL , NULL , NULL ) != D3D_OK ){
			DXASSERT( hr );
		}
	}
};