/**
 * $ Header: $
 */

#include "system/TimeOutException.h"

namespace zefiro_thread {
	TimeOutException::TimeOutException( zefiro_std::SourceLine sourceLine ,
		std::string additionalMessage):Exception( additionalMessage , sourceLine ){
	}
	TimeOutException::TimeOutException( const TimeOutException &other ):Exception( other){
	}
	TimeOutException::~TimeOutException(){
	}
	TimeOutException &TimeOutException::operator =( const TimeOutException &other ){
		Exception::operator =( other );
		return *this;
	}
	zefiro_std::Exception *TimeOutException::clone() const{
		return new TimeOutException( *this );
	}
	bool TimeOutException::isInstanceOf( const zefiro_std::Exception::Type &exceptionType  ) const{
	  return exceptionType == type()  ||
		Exception::isInstanceOf( exceptionType );
	}

	zefiro_std::Exception::Type TimeOutException::type(){
		return zefiro_std::Exception::Type( "zefiro_thread::TimeOutException" );
	}
};