#pragma once

#include <windows.h>
#include <d3d8.h>
#include "device.h"
#include "logger.h"

class D3D {
public:
	D3D():d3d_(NULL){
		d3d_ = Direct3DCreate8(D3D_SDK_VERSION);
		if( d3d_ == NULL ){
			DXERROR_LOG( NULL );
		}
	}
	Device *createDevice( HWND hWnd , bool windowed ){
		return new Device( hWnd , d3d_ , windowed );
	}
	virtual ~D3D(){
		if( d3d_ != NULL ){
			d3d_->Release();
		}
	}
protected:
	LPDIRECT3D8	d3d_;
};