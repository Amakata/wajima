/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/system/IllegalThreadStateException.h,v 1.2 2002/11/14 16:53:22 ama Exp $
 */

#ifndef __ILLEGALTHREADSTATEEXCEPTION_H__
#define __ILLEGALTHREADSTATEEXCEPTION_H__

#include "std/Exception.h"

namespace zefiro_system {
	class IllegalThreadStateException : public zefiro_std::Exception
	{
	public:
		IllegalThreadStateException( std::string message = ""  , zefiro_std::SourceLine sourceLine = zefiro_std::SourceLine()
                     );
		IllegalThreadStateException( std::string message , long lineNumber, std::string fileName );
		IllegalThreadStateException( const IllegalThreadStateException &other );
		virtual ~IllegalThreadStateException();
		std::string additionalMessage() const;
		/** Copy operator.
		* @param other Object to copy.
		* @return Reference on this object.
		*/
		IllegalThreadStateException &operator =( const IllegalThreadStateException &other );
		zefiro_std::Exception *clone() const;
		bool isInstanceOf( const zefiro_std::Exception::Type &type ) const;
		static zefiro_std::Exception::Type type();

	};
};


#endif //__ILLEGALTHREADSTATEEXCEPTION_H__