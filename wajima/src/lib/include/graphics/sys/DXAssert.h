/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/include/graphics/sys/Attic/DXAssert.h,v 1.1 2002/04/29 18:41:02 ama Exp $
 */
#ifndef __DXEXCEPTION_H__
#define __DXEXCEPTION_H__

#include <D3D8.h>

#include <std/SourceLine.h>

#define DXASSERT( HRESULT ) ::zefiro_graphics::DXAssert::DXAssert( HRESULT , ZEFIRO_STD_SOURCELINE() );
#define DXASSERT_MESSAGE( HRESLT  , MESSAGE ) ::zefiro_graphics::DXAssert::DXAssert( HRESULT , ZEFIRO_STD_SOURCELINE() , MESSAGE );

namespace zefiro_graphics {
	namespace DXAssert {
		void DXAssert( HRESULT hr , ::zefiro_std::SourceLine sourceLine , std::string message ="" );
	};
};

#endif //__DXEXCEPTION_H__