/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/graphics/GraphicsManager.h,v 1.1 2002/11/13 18:28:08 ama Exp $
 */
#ifndef __GRAPHICSMANAGER_H__
#define __GRAPHICSMANAGER_H__

#include <windows.h>
#include <d3d8.h>
#include "SmartPtr.h"
#include "graphics/GraphicsDevice.h"

namespace zefiro_graphics {
	class GraphicsManager {
	public:
		static Loki::SmartPtr<GraphicsManager> createGM( HWND );
		virtual ~GraphicsManager();
		Loki::SmartPtr<GraphicsDevice> createGD( int , int , int , bool );
	protected:
		GraphicsManager( HWND );
		LPDIRECT3D8	d3d_;
		HWND hwnd_;
	};
};
#endif //__GRAPHICSMANAGER_H__