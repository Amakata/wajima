#include <graphics/sys/GraphicsMode.h>

namespace zefiro_graphics {
	GraphicsMode::GraphicsMode( const int modeNumber , const int width , const int height , const int refreshRate , const D3DFORMAT format )
		:_modeNumber(modeNumber),_width(width),_height(height),_refreshRate(refreshRate),_d3dFormat(format){
	}
	GraphicsMode::GraphicsMode( const GraphicsMode &graphicsMode ){
		_modeNumber = graphicsMode._modeNumber;
		_width = graphicsMode._width;
		_height = graphicsMode._height;
		_refreshRate = graphicsMode._refreshRate;
		_d3dFormat = graphicsMode._d3dFormat;

	}
	GraphicsMode::~GraphicsMode(){
	}
	GraphicsMode& GraphicsMode::operator=( const GraphicsMode &graphicsMode ){
		_modeNumber = graphicsMode._modeNumber;
		_width = graphicsMode._width;
		_height = graphicsMode._height;
		_refreshRate = graphicsMode._refreshRate;
		_d3dFormat = graphicsMode._d3dFormat;
		return *this;
	}
	int GraphicsMode::getModeNumber() const{
		return _modeNumber;
	}
	int GraphicsMode::getWidth() const{
		return _width;
	}
	int GraphicsMode::getHeight() const{
		return _height;
	}
	int	GraphicsMode::getRefreshRate() const{
		return _refreshRate;
	}
	D3DFORMAT GraphicsMode::getFormat() const{
		return _d3dFormat;
	}
};