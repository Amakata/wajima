/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/include/lib/graphics/sys/Attic/Mode.h,v 1.2 2002/08/25 10:47:42 ama Exp $
 */

#ifndef __MODE_H__
#define __MODE_H__

#include <D3d8.h>
#include <string>

namespace zefiro_graphics {
	class Mode
	{
	public:
		Mode(const int width , const int height , const int refreshRate , const D3DFORMAT format );
		Mode( const Mode &mode );
		virtual ~Mode();
		Mode& operator=( const Mode &mode );
		int getWidth() const;
		int getHeight() const;
		int	getRefreshRate() const;
		D3DFORMAT getFormat() const;
		std::string toString() const;
	private:
		int _width;
		int _height;
		int _refreshRate;
		D3DFORMAT _d3dFormat;
	};
};

#endif //__MODE_H__