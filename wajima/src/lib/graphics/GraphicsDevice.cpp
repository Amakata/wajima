/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/graphics/GraphicsDevice.cpp,v 1.2 2002/12/13 21:17:28 ama Exp $
 */

#include "GraphicsDevice.h"

namespace zefiro_graphics {
	GraphicsDevice::GraphicsDevice( LPDIRECT3DDEVICE8 device ):device_(device){
	}
	GraphicsDevice::~GraphicsDevice(){
		device_->Release();
	}
};