/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/system/TimeOutException.cpp,v 1.3 2002/05/25 16:01:10 ama Exp $
 */

#include "system/TimeOutException.h"

namespace zefiro_system {
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
		return zefiro_std::Exception::Type( "zefiro_system::TimeOutException" );
	}
};