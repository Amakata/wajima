/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/graphics/GraphicsManager.h,v 1.9 2002/12/15 20:07:56 ama Exp $
 */
#ifndef __GRAPHICSMANAGER_H__
#define __GRAPHICSMANAGER_H__

#include <windows.h>
#include <d3d8.h>

#include "SmartPtr.h"
#include "GraphicsDevice.h"
#include "ColorFormat.h"

namespace zefiro_graphics {
	class GraphicsManager {
	public:
		typedef Loki::SmartPtr<GraphicsManager> GM;
		static GM createGM( HWND hwnd );
		virtual ~GraphicsManager();
		GraphicsDevice::GD createGD( int width , int height , ColorFormat back , DepthFormat depth ,  bool windowed , bool hal = true , bool threaded = false , int adapterNumber = 0 , int refreshRate = 0 );
	protected:
		GraphicsManager( HWND );
		LPDIRECT3D8	d3d_;
		HWND hwnd_;
	private:
		GraphicsManager();
		GraphicsManager( const GraphicsManager& );
		GraphicsManager& operator=( const GraphicsManager& );
	};
};
#endif //__GRAPHICSMANAGER_H__