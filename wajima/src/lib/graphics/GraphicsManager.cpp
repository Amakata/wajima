/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/graphics/GraphicsManager.cpp,v 1.1 2002/11/13 18:28:08 ama Exp $
 */

#include "GraphicsManager.h"
#include "std/Exception.h"
#include "std/InvalidArgument.h"

namespace zefiro_graphics {
	Loki::SmartPtr<GraphicsManager> GraphicsManager::createGM( HWND hwnd ){
		if( hwnd == 0 ){
			throw zefiro_std::InvalidArgument();
		}
		return Loki::SmartPtr<GraphicsManager>(new GraphicsManager( hwnd ));
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
	Loki::SmartPtr<GraphicsDevice> GraphicsManager::createGD( int width , int height , int color , bool windowed ){
		return Loki::SmartPtr<GraphicsDevice>( NULL );
	}
};
