/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/graphics/sys/Attic/Mode.cpp,v 1.4 2002/08/25 12:01:57 ama Exp $
 */

#include "graphics/sys/Mode.h"

#include <sstream>

namespace zefiro_graphics {
	Mode::Mode(  const int width , const int height , const int refreshRate , const D3DFORMAT format )
		:_width(width),_height(height),_refreshRate(refreshRate),_d3dFormat(format){
	}
	Mode::Mode( const Mode &mode ){
		_width = mode._width;
		_height = mode._height;
		_refreshRate = mode._refreshRate;
		_d3dFormat = mode._d3dFormat;

	}
	Mode::~Mode(){
	}
	Mode& Mode::operator=( const Mode &mode ){
		_width = mode._width;
		_height = mode._height;
		_refreshRate = mode._refreshRate;
		_d3dFormat = mode._d3dFormat;
		return *this;
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