#ifndef __D3D8_H__
#define __D3D8_H__

#include <d3d8.h>

namespace zefiro_graphics {
	class D3D8
	{
	public:
		D3D8();
		virtual ~D3D8();
	protected:
		LPDIRECT3D8 _pD3D;
	private:
		D3D8( const D3D8  & d3d8 );
		D3D8 operator = ( const D3D8  & d3d8 );
	};
};

#endif //__D3D8_H__