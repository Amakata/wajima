#include "std/InvalidArgument.h"

namespace zefiro_std {
	InvalidArgument::InvalidArgument( SourceLine sourceLine ,
		std::string additionalMessage):Exception( additionalMessage , sourceLine ){
	}
	InvalidArgument::InvalidArgument( const InvalidArgument &other ):Exception( other){
	}
	InvalidArgument::~InvalidArgument(){
	}
	InvalidArgument &InvalidArgument::operator =( const InvalidArgument &other ){
		Exception::operator =( other );
		return *this;
	}
	Exception *InvalidArgument::clone() const{
		return new InvalidArgument( *this );
	}
	bool InvalidArgument::isInstanceOf( const Type &exceptionType  ) const{
	  return exceptionType == type()  ||
		Exception::isInstanceOf( exceptionType );
	}

	Exception::Type InvalidArgument::type(){
		return Type( "zefiro_std::InvalidArgument" );
	}
};