/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/system/TimeOutException.cpp,v 1.5 2002/11/14 16:53:01 ama Exp $
 */

#include "TimeOutException.h"

namespace zefiro_system {
	TimeOutException::TimeOutException( std::string message , zefiro_std::SourceLine sourceLine ):Exception( message , sourceLine ){
	}
	TimeOutException::TimeOutException( std::string message , long lineNumber , std::string fileName ):Exception( message , lineNumber , fileName ){
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
		return zefiro_std::Exception::Type( "zefiro_system::TimeOutException" );
	}
};