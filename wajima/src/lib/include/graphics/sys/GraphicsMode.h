#ifndef __GRAPHICSMODE_H__
#define __GRAPHICSMODE_H__

#include <D3d8.h>

namespace zefiro_graphics {
	class GraphicsMode
	{
	public:
		GraphicsMode( const int modeNumber , const int width , const int height , const int refreshRate , const D3DFORMAT format );
		GraphicsMode( const GraphicsMode &graphicsMode );
		virtual ~GraphicsMode();
		GraphicsMode& operator=( const GraphicsMode &graphicsMode );
		int getModeNumber() const;
		int getWidth() const;
		int getHeight() const;
		int	getRefreshRate() const;
		D3DFORMAT getFormat() const;
	private:
		int _modeNumber;
		int _width;
		int _height;
		int _refreshRate;
		D3DFORMAT _d3dFormat;
	};
};

#endif //__GRAPHICSADAPTERMODE_H__