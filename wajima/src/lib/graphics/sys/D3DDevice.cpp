/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/graphics/sys/Attic/D3DDevice.cpp,v 1.1 2002/08/13 06:49:14 ama Exp $
 */

#include "graphics/sys/D3DDevice.h"

namespace zefiro_graphics {
	D3DDevice::D3DDevice( LPDIRECT3DDEVICE8 d3ddevice8 ):pD3DDevice8_(d3ddevice8){
	}
	D3DDevice::~D3DDevice(){
		pD3DDevice8_->Release();
	}
};