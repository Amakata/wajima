#include <graphics/sys/Mode.h>

#include <sstream>

namespace zefiro_graphics {
	Mode::Mode( const int modeNumber , const int width , const int height , const int refreshRate , const D3DFORMAT format )
		:_modeNumber(modeNumber),_width(width),_height(height),_refreshRate(refreshRate),_d3dFormat(format){
	}
	Mode::Mode( const Mode &mode ){
		_modeNumber = mode._modeNumber;
		_width = mode._width;
		_height = mode._height;
		_refreshRate = mode._refreshRate;
		_d3dFormat = mode._d3dFormat;

	}
	Mode::~Mode(){
	}
	Mode& Mode::operator=( const Mode &mode ){
		_modeNumber = mode._modeNumber;
		_width = mode._width;
		_height = mode._height;
		_refreshRate = mode._refreshRate;
		_d3dFormat = mode._d3dFormat;
		return *this;
	}
	int Mode::getModeNumber() const{
		return _modeNumber;
	}
	int Mode::getWidth() const{
		return _width;
	}
	int Mode::getHeight() const{
		return _height;
	}
	int	Mode::getRefreshRate() const{
		return _refreshRate;
	}
	D3DFORMAT Mode::getFormat() const{
		return _d3dFormat;
	}
	std::string Mode::toString() const{
		std::ostringstream result;
		result << _width << " " << _height << " " << _refreshRate << " " << _d3dFormat;
		return result.str();
	}
};