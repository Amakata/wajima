/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/std/sys/Win32Assert.cpp,v 1.4 2002/11/04 16:29:38 ama Exp $
 */

#include "Win32Assert.h"

#include <string>
#include <windows.h>

namespace zefiro_std {
	namespace Win32Assert {
		void Win32Assert( DWORD result , ::zefiro_std::SourceLine sourceLine , std::string message ){
			switch( result ){
			case ERROR_SUCCESS:
				break;
			default:
				TCHAR *tcMessage;
				if( 0 == FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS |FORMAT_MESSAGE_FROM_SYSTEM , NULL , result , MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),(LPTSTR)&tcMessage , 0 , NULL ) ){
					throw ::zefiro_std::Win32Exception( GetLastError() , ZEFIRO_STD_SOURCELINE() , "" );
				}
				throw ::zefiro_std::Win32Exception( result , sourceLine , std::string(tcMessage)+message );
			}
		}
	};
};