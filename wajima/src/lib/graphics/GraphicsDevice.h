/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/graphics/GraphicsDevice.h,v 1.6 2002/12/15 10:38:25 ama Exp $
 */

#ifndef __GRAPHICSDEVICE_H__
#define __GRAPHICSDEVICE_H__

#include <d3d8.h>

#include "SmartPtr.h"
#include "ColorFormat.h"
#include "DepthFormat.h"
#include "Color.h"

namespace zefiro_graphics {
	class GraphicsDevice {
	public:
		typedef Loki::SmartPtr<GraphicsDevice> GD;
		virtual ~GraphicsDevice();
		void clear( Color & , float depth );
	protected:
		friend class GraphicsManager;
		GraphicsDevice( LPDIRECT3DDEVICE8 device );
	private:
		LPDIRECT3DDEVICE8 device_;

		GraphicsDevice();
		GraphicsDevice( const GraphicsDevice & );
		GraphicsDevice& operator=( const GraphicsDevice & );
	};
};
#endif //__GRAPHICSDEVICE_H__