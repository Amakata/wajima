/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/graphics/sys/Attic/D3D8.h,v 1.1 2002/11/03 09:04:44 ama Exp $
 */

#ifndef __D3D8_H__
#define __D3D8_H__

#include <d3d8.h>

#include "graphics/sys/Adapter.h"
#include "graphics/sys/D3DDevice.h"

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
		D3DDevice* createDevice( const int adapterid , Mode &mode , bool windowed , bool threaded , HWND hwnd ) const; 
	protected:
		std::string getAdapterIdentifier( const int adapterid ) const;
		Mode getAdapterMode( const int adapterid , const int modeid ) const;
		LPDIRECT3D8 d3d_;
	private:
		D3D8( const D3D8  & d3d8 );
		D3D8 operator = ( const D3D8  & d3d8 );
	};
};

#endif //__D3D8_H__