/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/std/sys/Win32Exception.cpp,v 1.4 2002/11/04 16:29:38 ama Exp $
 */

#include "Win32Exception.h"

namespace zefiro_std {
	Win32Exception::Win32Exception( DWORD errorCode , zefiro_std::SourceLine sourceLine ,
		std::string additionalMessage ):Exception(additionalMessage,sourceLine),_errorCode(errorCode){
	}
	Win32Exception::Win32Exception( DWORD errorCode , long lineNumber, 
		std::string fileName ,std::string additionalMessage ):Exception(additionalMessage,lineNumber,fileName),_errorCode(errorCode){
	}
	Win32Exception::Win32Exception( const Win32Exception &other ):Exception(other),_errorCode(other._errorCode){
	}
	Win32Exception::~Win32Exception() throw(){
	}
	DWORD Win32Exception::getError() const{
		return _errorCode;
	}
	Win32Exception &Win32Exception::operator =( const Win32Exception &other ){
		Exception::operator =( other );
		_errorCode = other._errorCode;
		return *this;
	}
	zefiro_std::Exception *Win32Exception::clone() const{
		return new Win32Exception( *this );
	}
	bool Win32Exception::isInstanceOf( const Type &exceptionType ) const{
		return exceptionType == type();
	}
	Exception::Type Win32Exception::type(){
		return Type( "zefiro_std::Win32Exception" );
	}
};