#include "graphics/sys/DxAssert.h"


#include <string>

#include <Dxerr8.h>

#include <std/InvalidArgument.h>

namespace zefiro_graphics {
	namespace DXAssert {
		void DXAssert( HRESULT hr , ::zefiro_std::SourceLine sourceLine , std::string message ){
			switch( hr ){
			case D3D_OK:
				return;
			default:
				const TCHAR *errChar = DXGetErrorString8( hr );
				std::string	errStr = std::string(errChar);

				switch( hr ){
				case D3DERR_INVALIDCALL:
					throw zefiro_std::InvalidArgument( sourceLine , errStr + "." + message );
				default:
					throw zefiro_std::Exception( "ó\ä˙ÇµÇ»Ç¢ÉGÉâÅ[Ç≈Ç∑." + errStr , sourceLine ); 
					break;
				}
				break;
			}
		}
	};
};