/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/graphics/GraphicsManager.cpp,v 1.6 2002/11/29 18:21:51 ama Exp $
 */

#include "GraphicsManager.h"
#include "std/Exception.h"
#include "std/InvalidArgument.h"
#include "sys/DXAssert.h"

namespace zefiro_graphics {
	GraphicsManager::GM GraphicsManager::createGM( HWND hwnd ){
		if( hwnd == 0 ){
			throw zefiro_std::InvalidArgument();
		}
		return GM(new GraphicsManager( hwnd ));
	}
	GraphicsManager::GraphicsManager( HWND hwnd ):hwnd_(hwnd){
		d3d_ = Direct3DCreate8(D3D_SDK_VERSION);
		if( d3d_ == NULL ){
			throw zefiro_std::Exception();
		}
	}
	GraphicsManager::~GraphicsManager(){
		if( d3d_ != NULL ){
			d3d_->Release();
		}
	}
};
