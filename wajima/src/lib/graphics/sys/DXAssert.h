/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/graphics/sys/DXAssert.h,v 1.2 2002/11/14 16:51:59 ama Exp $
 */
#ifndef __DXASSERT_H__
#define __DXASSERT_H__

#include <D3D8.h>

#include "std/SourceLine.h"

#define DXASSERT( HRESULT ) ::zefiro_graphics::DXAssert::DXAssert( "" , HRESULT , ZEFIRO_STD_SOURCELINE() );
#define DXASSERT_MESSAGE( MESSAGE , HRESULT  ) ::zefiro_graphics::DXAssert::DXAssert( MESSAGE , HRESULT , ZEFIRO_STD_SOURCELINE() );

namespace zefiro_graphics {
	namespace DXAssert {
		void DXAssert( std::string message , HRESULT hr , ::zefiro_std::SourceLine sourceLine );
	};
};

#endif //__DXASSERT_H__