/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/graphics/GraphicsManager.h,v 1.5 2002/11/29 18:21:13 ama Exp $
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
	protected:
		GraphicsManager( HWND );
		LPDIRECT3D8	d3d_;
		HWND hwnd_;
	};
};
#endif //__GRAPHICSMANAGER_H__