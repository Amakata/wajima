#ifndef __MODE_H__
#define __MODE_H__

#include <D3d8.h>
#include <string>

namespace zefiro_graphics {
	class Mode
	{
	public:
		Mode( const int modeNumber , const int width , const int height , const int refreshRate , const D3DFORMAT format );
		Mode( const Mode &mode );
		virtual ~Mode();
		Mode& operator=( const Mode &mode );
		int getModeNumber() const;
		int getWidth() const;
		int getHeight() const;
		int	getRefreshRate() const;
		D3DFORMAT getFormat() const;
		std::string toString() const;
	private:
		int _modeNumber;
		int _width;
		int _height;
		int _refreshRate;
		D3DFORMAT _d3dFormat;
	};
};

#endif //__MODE_H__