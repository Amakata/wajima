/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/include/lib/graphics/sys/Attic/DXAssert.h,v 1.2 2002/05/23 15:59:16 ama Exp $
 */
#ifndef __DXASSERT_H__
#define __DXASSERT_H__

#include <D3D8.h>

#include "std/SourceLine.h"

#define DXASSERT( HRESULT ) ::zefiro_graphics::DXAssert::DXAssert( HRESULT , ZEFIRO_STD_SOURCELINE() );
#define DXASSERT_MESSAGE( HRESULT  , MESSAGE ) ::zefiro_graphics::DXAssert::DXAssert( HRESULT , ZEFIRO_STD_SOURCELINE() , MESSAGE );

namespace zefiro_graphics {
	namespace DXAssert {
		void DXAssert( HRESULT hr , ::zefiro_std::SourceLine sourceLine , std::string message ="" );
	};
};

#endif //__DXASSERT_H__