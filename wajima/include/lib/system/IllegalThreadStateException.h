/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/include/lib/system/Attic/IllegalThreadStateException.h,v 1.3 2002/05/25 15:58:21 ama Exp $
 */

#ifndef __ILLEGALTHREADSTATEEXCEPTION_H__
#define __ILLEGALTHREADSTATEEXCEPTION_H__

#include "std/Exception.h"

namespace zefiro_system {
	class IllegalThreadStateException : public zefiro_std::Exception
	{
	public:
		IllegalThreadStateException( zefiro_std::SourceLine sourceLine = zefiro_std::SourceLine(),
                     std::string additionalMessage = "" );
		IllegalThreadStateException( long lineNumber, 
                     std::string fileName ,std::string additionalMessage = "");
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