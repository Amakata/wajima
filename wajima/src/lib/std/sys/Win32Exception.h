/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/std/sys/Win32Exception.h,v 1.3 2002/11/14 16:52:53 ama Exp $
 */
#ifndef __WIN32EXCEPTION_H__
#define __WIN32EXCEPTION_H__

#include "../Exception.h"
#include <windows.h>

namespace zefiro_std {
	class Win32Exception : public Exception 
	{
	public:
		Win32Exception( std::string message , DWORD errorCode , zefiro_std::SourceLine sourceLine = zefiro_std::SourceLine()  );
		Win32Exception( std::string message , DWORD errorCode , long lineNumber, std::string fileName);
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