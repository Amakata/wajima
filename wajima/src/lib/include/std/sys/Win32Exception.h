#ifndef __WIN32EXCEPTION_H__
#define __WIN32EXCEPTION_H__
/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/include/std/sys/Attic/Win32Exception.h,v 1.1 2002/05/08 15:19:08 ama Exp $
 */

#include "std/Exception.h"
#include <windows.h>

namespace zefiro_std {
	class Win32Exception : public Exception 
	{
	public:
		Win32Exception( DWORD errorCode , zefiro_std::SourceLine sourceLine = zefiro_std::SourceLine() , std::string additionalMessage = "" );
		Win32Exception( DWORD errorCode , long lineNumber, std::string fileName ,std::string additionalMessage = "");
		Win32Exception( const Win32Exception &other );
		virtual ~Win32Exception() throw();
		DWORD getError() const;
		/** Copy operator.
		* @param other Object to copy.
		* @return Reference on this object.
		*/
		Win32Exception &operator =( const Win32Exception &other );
		zefiro_std::Exception *clone() const;
		bool isInstanceOf( const Type &type ) const;
		static Type type();
	protected:
		DWORD _errorCode;
	};
};

#endif //__WIN32EXCEPTION_H__