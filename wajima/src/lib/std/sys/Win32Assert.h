/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/std/sys/Win32Assert.h,v 1.3 2002/11/14 16:52:53 ama Exp $
 */
#ifndef __WIN32ASSERT_H__
#define __WIN32ASSERT_H__

#include <windows.h>

#include "../SourceLine.h"
#include "Win32Exception.h"

#define WIN32ASSERT( RESULT ) ::zefiro_std::Win32Assert::Win32Assert( "" , RESULT , ZEFIRO_STD_SOURCELINE() );
#define WIN32ASSERT_MESSAGE( MESSAGE , RESULT ) ::zefiro_std::Win32Assert::Win32Assert( MESSAGE , RESULT , ZEFIRO_STD_SOURCELINE() );

namespace zefiro_std {
	namespace Win32Assert {
		void Win32Assert( std::string message , DWORD result , ::zefiro_std::SourceLine sourceLine  );
	};
};



#endif //__WIN32ASSERT_H__