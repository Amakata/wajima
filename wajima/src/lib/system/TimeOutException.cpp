/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/system/TimeOutException.cpp,v 1.4 2002/11/04 16:29:19 ama Exp $
 */

#include "TimeOutException.h"

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