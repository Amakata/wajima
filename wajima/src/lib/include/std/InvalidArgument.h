#ifndef __INVALIDARGUMENT_H__
#define __INVALIDARGUMENT_H__

#include "std/Exception.h"

namespace zefiro_std {
	class InvalidArgument : public Exception
	{
	public:
		InvalidArgument( SourceLine sourceLine = SourceLine(),
                     std::string additionalMessage = "" );
		InvalidArgument( long lineNumber, 
                     std::string fileName ,std::string additionalMessage = "");
		InvalidArgument( const InvalidArgument &other );
		virtual ~InvalidArgument() throw();
		std::string additionalMessage() const;
		/** Copy operator.
		* @param other Object to copy.
		* @return Reference on this object.
		*/
		InvalidArgument &operator =( const InvalidArgument &other );
		Exception *clone() const;
		bool isInstanceOf( const Type &type ) const;
		static Type type();

	};
};


#endif //__INVALIDARGUMENT_H__