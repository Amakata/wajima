/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/graphics/GraphicsManager.h,v 1.2 2002/11/24 14:51:06 ama Exp $
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
	class GraphicsDeviceModeFilter : public std::unary_function<std::vector<GraphicsDeviceMode>,std::vector<GraphicsDeviceMode> > {
	public:
		virtual result_type operator()(argument_type gdms){
			return (result_type)gdms;
		}
	};

	class GraphicsManager {
	public:
		typedef Loki::SmartPtr<GraphicsManager> GM;
		typedef std::vector<GraphicsDeviceMode> GDM_CONTAINERd;
		static GM createGM( HWND hwnd );
		virtual ~GraphicsManager();
		GraphicsDevice::GD createGD( int width , int height , ColorFormat , int refreshRate , bool windowed );
		GraphicsDevice::GD createGD( GraphicsDeviceMode gdm );
		std::vector<GraphicsDeviceMode> queryGD( std::unary_function<std::vector<GraphicsDeviceMode>,std::vector<GraphicsDeviceMode> > &queryFunc = AllGraphicsDevice() );
	protected:
		GraphicsManager( HWND );
		LPDIRECT3D8	d3d_;
		HWND hwnd_;
	};
};
#endif //__GRAPHICSMANAGER_H__