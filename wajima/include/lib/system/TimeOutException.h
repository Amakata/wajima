/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/include/lib/system/Attic/TimeOutException.h,v 1.3 2002/05/25 15:58:25 ama Exp $
 */

#ifndef __TIMEOUTEXCEPTION_H__
#define __TIMEOUTEXCEPTION_H__

#include "std/Exception.h"

namespace zefiro_system {
	class TimeOutException : public zefiro_std::Exception
	{
	public:
		TimeOutException ( zefiro_std::SourceLine sourceLine = zefiro_std::SourceLine(),
                     std::string additionalMessage = "" );
		TimeOutException ( long lineNumber, 
                     std::string fileName ,std::string additionalMessage = "");
		TimeOutException ( const TimeOutException  &other );
		virtual ~TimeOutException ();
		std::string additionalMessage() const;
		/** Copy operator.
		* @param other Object to copy.
		* @return Reference on this object.
		*/
		TimeOutException  &operator =( const TimeOutException  &other );
		zefiro_std::Exception *clone() const;
		bool isInstanceOf( const zefiro_std::Exception::Type &type ) const;
		static zefiro_std::Exception::Type type();

	};
};


#endif //__TIMEOUTEXCEPTION_H__