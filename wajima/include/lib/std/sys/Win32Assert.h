#ifndef __WIN32ASSERT_H__
#define __WIN32ASSERT_H__
/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/include/lib/std/sys/Attic/Win32Assert.h,v 1.1 2002/05/10 19:31:04 ama Exp $
 */

#include <windows.h>

#include "std/SourceLine.h"
#include "std/sys/Win32Exception.h"

#define WIN32ASSERT( RESULT ) ::zefiro_std::Win32Assert::Win32Assert( RESULT , ZEFIRO_STD_SOURCELINE() );
#define WIN32ASSERT_MESSAGE( MESSAGE ) ::zefiro_std::Win32Assert::Win32Assert( RESULT , ZEFIRO_STD_SOURCELINE() , MESSAGE );

namespace zefiro_std {
	namespace Win32Assert {
		void Win32Assert( DWORD result , ::zefiro_std::SourceLine sourceLine , std::string message ="" );
	};
};



#endif //__WIN32ASSERT_H__