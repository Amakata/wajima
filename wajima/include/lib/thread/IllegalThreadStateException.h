#ifndef __ILLEGALTHREADSTATEEXCEPTION_H__
#define __ILLEGALTHREADSTATEEXCEPTION_H__

/**
 * $ Header: $
 */

#include "std/Exception.h"

namespace zefiro_thread {
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