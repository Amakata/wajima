#include "graphics/sys/DxAssert.h"


#include <string>

#include <Dxerr8.h>

#include "graphics/sys/DXException.h"
#include "graphics/sys/DXInvalidArgument.h"

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

					throw zefiro_graphics::DXInvalidArgument( hr , sourceLine , errStr + "." + message );
					break;
				default:
					throw zefiro_graphics::DXException( hr , sourceLine , "ó\ä˙ÇµÇ»Ç¢ÉGÉâÅ[Ç≈Ç∑." + errStr + "." + message ); 
					break;
				}
				break;
			}
		}
	};
};