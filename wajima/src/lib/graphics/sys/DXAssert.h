/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/graphics/sys/DXAssert.h,v 1.1 2002/11/03 09:04:44 ama Exp $
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