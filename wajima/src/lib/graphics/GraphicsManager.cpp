/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/graphics/GraphicsManager.cpp,v 1.2 2002/11/24 14:53:35 ama Exp $
 */

#include "GraphicsManager.h"
#include "std/Exception.h"
#include "std/InvalidArgument.h"

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
	GraphicsDevice::GD GraphicsManager::createGD( int width , int height , ColorFormat colorFormat , int refreshRate , bool windowed ){
		return GraphicsDevice::GD( NULL );
	}
	GraphicsDevice::GD GraphicsManager::createGD( GraphicsDeviceMode gdm ){
		return GraphicsDevice::GD( NULL );
	}
	std::vector<GraphicsDeviceMode> GraphicsManager::queryGD( std::unary_function<std::vector<GraphicsDeviceMode>,std::vector<GraphicsDeviceMode> > &queryFunc ){
		std::vector<GraphicsDeviceMode> result;
		queryFunc( result );
		return result;
	}
};
