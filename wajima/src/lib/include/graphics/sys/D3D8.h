/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/include/graphics/sys/Attic/D3D8.h,v 1.8 2002/04/29 16:28:02 ama Exp $
 */

#ifndef __D3D8_H__
#define __D3D8_H__

#include <d3d8.h>

#include "graphics/sys/Adapter.h"

namespace zefiro_graphics {
	class D3D8
	{
	public:
		D3D8();
		virtual ~D3D8();
		int getAdapterCount() const;
		int getAdapterModeCount( const int adapter ) const;
		bool isAvailable() const;
		std::vector<Adapter> getAdapterVector() const;
	protected:
		std::string getAdapterIdentifier( const int adapterid ) const;
		Mode getAdapterMode( const int adapterid , const int modeid ) const;
		LPDIRECT3D8 _pD3D;
	private:
		D3D8( const D3D8  & d3d8 );
		D3D8 operator = ( const D3D8  & d3d8 );
	};
};

#endif //__D3D8_H__