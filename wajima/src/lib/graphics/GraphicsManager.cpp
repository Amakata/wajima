/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/graphics/GraphicsManager.cpp,v 1.8 2002/12/15 20:07:56 ama Exp $
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
	GraphicsDevice::GD GraphicsManager::createGD(
		int width , int height , 
		ColorFormat back , DepthFormat depth , 
		bool windowed , bool hal , bool threaded , int adapterNumber , int refreshRate ){
			LPDIRECT3DDEVICE8		result;
			D3DPRESENT_PARAMETERS	param;
			if( d3d_ == NULL ){
				throw zefiro_std::Exception();
			}
			param.AutoDepthStencilFormat = convertDepthFormatToD3DFORMAT( depth );
			param.BackBufferCount = 1;
			param.BackBufferFormat = convertColorFormatToD3DFORMAT( back );
			param.BackBufferHeight = height;
			param.BackBufferWidth = width;
			param.EnableAutoDepthStencil = ( depth.getBitLength() != 0 );
			param.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
			param.MultiSampleType = D3DMULTISAMPLE_NONE;
			param.Windowed = windowed;
			param.FullScreen_RefreshRateInHz = windowed ? 0 : refreshRate;
			param.FullScreen_PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
			param.hDeviceWindow = hwnd_;
			param.SwapEffect = D3DSWAPEFFECT_DISCARD;
			D3DDEVTYPE type = hal ? D3DDEVTYPE_HAL : D3DDEVTYPE_REF;
			DWORD flag = threaded ?  D3DCREATE_MULTITHREADED : NULL ;
			if( HRESULT hr = d3d_->CreateDevice( adapterNumber , type , hwnd_ , flag | D3DCREATE_HARDWARE_VERTEXPROCESSING , &param , &result ) != D3D_OK ){
				if( HRESULT hr = d3d_->CreateDevice( adapterNumber , type , hwnd_ , flag | D3DCREATE_SOFTWARE_VERTEXPROCESSING , &param , &result ) != D3D_OK ){
					DXASSERT(hr);
				}
			}
			return GraphicsDevice::GD( new GraphicsDevice( result ) );
	}
};
