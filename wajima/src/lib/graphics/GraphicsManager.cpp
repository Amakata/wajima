/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/graphics/GraphicsManager.cpp,v 1.5 2002/11/26 11:26:24 ama Exp $
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
	GraphicsDevice::GD GraphicsManager::createGD( int width , int height , ColorFormat colorFormat , int refreshRate , bool windowed , int adapterNumber ){
		// TODO: GDの作成を正しくやるためのルーチンをかかねば・・・。しくしく。
		D3DPRESENT_PARAMETERS d3dParams = {0};
		d3dParams.Windowed = windowed;
		d3dParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dParams.BackBufferHeight = height;
		d3dParams.BackBufferWidth = width;
		d3dParams.BackBufferCount = 1;
		d3dParams.EnableAutoDepthStencil = TRUE;
		d3dParams.FullScreen_RefreshRateInHz = refreshRate;

		return GraphicsDevice::GD( NULL );
	}
	GraphicsDevice::GD GraphicsManager::createGD( GraphicsDeviceMode gdm ){
		return createGD( gdm.getWidth() , gdm.getHeight() , gdm.getColorFormat() , gdm.getRefreshRate() , gdm.isWindowed() , gdm.getAdapterNumber() );
	}
	GraphicsDevice::GD GraphicsManager::createGD( GraphicsDeviceModeSelector &selector ){
		return createGD( selector( queryGD() ) );
	}
	std::vector<GraphicsDeviceMode> GraphicsManager::queryGD( GraphicsDeviceModeFilter &filter ){
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
						format = ColorFormat::R8G8B8;
						break;
					case D3DFMT_A8R8G8B8:
						format = ColorFormat::A8R8G8B8;
						break;
					case D3DFMT_X8R8G8B8:
						format = ColorFormat::X8R8G8B8;
						break;
					case D3DFMT_R5G6B5:
						format = ColorFormat::R5G6B5;
						break;
					case D3DFMT_X1R5G5B5:
						format = ColorFormat::X1R5G5B5;
						break;
					case D3DFMT_A1R5G5B5:
						format = ColorFormat::A1R5G5B5;
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
		return filter( result );
	}
};
