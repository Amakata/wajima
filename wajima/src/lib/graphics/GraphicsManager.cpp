/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/graphics/GraphicsManager.cpp,v 1.3 2002/11/24 17:41:55 ama Exp $
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
	GraphicsDevice::GD GraphicsManager::createGD( int width , int height , ColorFormat colorFormat , int refreshRate , bool windowed ){
		return GraphicsDevice::GD( NULL );
	}
	GraphicsDevice::GD GraphicsManager::createGD( GraphicsDeviceMode gdm ){
		return GraphicsDevice::GD( NULL );
	}
	GraphicsDevice::GD GraphicsManager::createGD( GraphicsDeviceModeSelector selector ){
		return GraphicsDevice::GD( NULL );
	}
	std::vector<GraphicsDeviceMode> GraphicsManager::queryGD( GraphicsDeviceModeSelector selector ){
		std::vector<GraphicsDeviceMode> result;
		int adapterCountSize = d3d_->GetAdapterCount();
		for( int adapterCount = 0 ; adapterCount < adapterCountSize ; ++adapterCount ){
			int deviceCountSize = d3d_->GetAdapterModeCount( adapterCountSize );
			for( int deviceCount = 0 ; deviceCount < deviceCountSize ; ++deviceCount ){
				D3DDISPLAYMODE mode;
				ColorFormat::FORMAT format;
				DXASSERT( d3d_->EnumAdapterModes( adapterCount , deviceCount , &mode ));
				switch( mode.Format ){
					case D3DFMT_R8G8B8:
						format = ColorFormat::RGB888;
						break;
					case D3DFMT_A8R8G8B8:
						format = ColorFormat::ARGB8888;
						break;
					case D3DFMT_X8R8G8B8:
						format = ColorFormat::XRGB8888;
						break;
					case D3DFMT_R5G6B5:
						format = ColorFormat::RGB565;
						break;
					case D3DFMT_X1R5G5B5:
						format = ColorFormat::XRGB1555;
						break;
					case D3DFMT_A1R5G5B5:
						format = ColorFormat::ARGB1555;
						break;
					default:
						continue;
				}
				if( D3D_OK == d3d_->CheckDeviceType( adapterCount , D3DDEVTYPE_HAL , mode.Format , mode.Format , false ) || 
					D3D_OK == d3d_->CheckDeviceType( adapterCount , D3DDEVTYPE_REF , mode.Format , mode.Format , false ) ){
					result.push_back( GraphicsDeviceMode( mode.Width , mode.Height , ColorFormat( format ) , mode.RefreshRate , false , adapterCount ) );
				}
				if( D3D_OK == d3d_->CheckDeviceType( adapterCount , D3DDEVTYPE_HAL , mode.Format , mode.Format , true ) || 
					D3D_OK == d3d_->CheckDeviceType( adapterCount , D3DDEVTYPE_REF , mode.Format , mode.Format , true ) ){
					result.push_back( GraphicsDeviceMode( mode.Width , mode.Height , ColorFormat( format ) , mode.RefreshRate , false , adapterCount ) );
				}
			}
		}
		return selector( result );
	}
};
