/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/graphics/GraphicsManager.h,v 1.4 2002/11/25 13:06:56 ama Exp $
 */
#ifndef __GRAPHICSMANAGER_H__
#define __GRAPHICSMANAGER_H__

#include <windows.h>
#include <d3d8.h>

#include <vector>
#include <functional>

#include "SmartPtr.h"
#include "GraphicsDevice.h"
#include "GraphicsDeviceMode.h"
#include "ColorFormat.h"

namespace zefiro_graphics {
	// queryGD用ファンクタ
	class GraphicsDeviceModeFilter {
	public:
		virtual std::vector<GraphicsDeviceMode> operator()(std::vector<GraphicsDeviceMode> gdms){
			return gdms;
		}
	};
	// createGD用ファンクタ
	class GraphicsDeviceModeSelector {
	public:
		virtual GraphicsDeviceMode operator()( std::vector<GraphicsDeviceMode> ) = 0;		
	};

	class GraphicsManager {
	public:
		typedef Loki::SmartPtr<GraphicsManager> GM;
		static GM createGM( HWND hwnd );
		virtual ~GraphicsManager();
		GraphicsDevice::GD createGD( int width , int height , ColorFormat colorFormat , int refreshRate , bool windowed , int adapterNumber );
		GraphicsDevice::GD createGD( GraphicsDeviceMode gdm );
		GraphicsDevice::GD createGD( GraphicsDeviceModeSelector &selector );
		std::vector<GraphicsDeviceMode> queryGD( GraphicsDeviceModeFilter &filter = GraphicsDeviceModeFilter() );
	protected:
		GraphicsManager( HWND );
		LPDIRECT3D8	d3d_;
		HWND hwnd_;
	};
};
#endif //__GRAPHICSMANAGER_H__