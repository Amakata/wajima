/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/graphics/sys/DXAssert.cpp,v 1.6 2002/11/14 16:51:59 ama Exp $
 */
#include "DxAssert.h"
#include <string>

#include <Dxerr8.h>

#include "DXException.h"
#include "DXInvalidArgument.h"

namespace zefiro_graphics {
	namespace DXAssert {
		void DXAssert( std::string message , HRESULT hr , ::zefiro_std::SourceLine sourceLine  ){
			switch( hr ){
			case D3D_OK:
				return;
			default:
				const TCHAR *errChar = DXGetErrorString8( hr );
				std::string	errStr = std::string(errChar);

				switch( hr ){
				case D3DERR_INVALIDCALL:

					throw zefiro_graphics::DXInvalidArgument( errStr + "." + message , hr , sourceLine  );
					break;
				default:
					throw zefiro_graphics::DXException( "ó\ä˙ÇµÇ»Ç¢ÉGÉâÅ[Ç≈Ç∑." + errStr + "." + message , hr , sourceLine  ); 
					break;
				}
				break;
			}
		}
	};
};