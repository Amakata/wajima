/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/system/IllegalThreadStateException.cpp,v 1.3 2002/05/25 16:01:10 ama Exp $
 */

#include "system/IllegalThreadStateException.h"

namespace zefiro_system {
	IllegalThreadStateException::IllegalThreadStateException( zefiro_std::SourceLine sourceLine ,
		std::string additionalMessage):Exception( additionalMessage , sourceLine ){
	}
	IllegalThreadStateException::IllegalThreadStateException( const IllegalThreadStateException &other ):Exception( other){
	}
	IllegalThreadStateException::~IllegalThreadStateException(){
	}
	IllegalThreadStateException &IllegalThreadStateException::operator =( const IllegalThreadStateException &other ){
		Exception::operator =( other );
		return *this;
	}
	zefiro_std::Exception *IllegalThreadStateException::clone() const{
		return new IllegalThreadStateException( *this );
	}
	bool IllegalThreadStateException::isInstanceOf( const zefiro_std::Exception::Type &exceptionType  ) const{
	  return exceptionType == type()  ||
		Exception::isInstanceOf( exceptionType );
	}

	zefiro_std::Exception::Type IllegalThreadStateException::type(){
		return zefiro_std::Exception::Type( "zefiro_system::IllegalThreadStateException" );
	}
};