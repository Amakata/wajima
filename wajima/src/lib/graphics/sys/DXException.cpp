/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/graphics/sys/DXException.cpp,v 1.4 2002/11/14 16:51:59 ama Exp $
 */

#include "DXException.h"

namespace zefiro_graphics {
	DXException::DXException( std::string message , HRESULT hr , zefiro_std::SourceLine sourceLine )
		: Exception(message , sourceLine),_hr(hr){
	}
	DXException::DXException( std::string message , HRESULT hr , long lineNumber , std::string fileName )
		: Exception(message,lineNumber,fileName),_hr(hr){
	}
	DXException::DXException( const DXException &other ):Exception(other),_hr(other._hr){
	}
	DXException::~DXException() throw(){
	}
	HRESULT DXException::getHResult() const{
		return _hr;
	}
	DXException &DXException::operator =( const DXException &other ){
		Exception::operator =(other);
		_hr = other._hr;
		return *this;
	}
	zefiro_std::Exception *DXException::clone() const{
		return new DXException( *this );
	}
	bool DXException::isInstanceOf( const zefiro_std::Exception::Type &exceptionType ) const{
	     return exceptionType == type()  ||
         Exception::isInstanceOf( exceptionType );
	}
	zefiro_std::Exception::Type DXException::type(){
		return zefiro_std::Exception::Type( "zefiro_graphics::DXException" );
	}
};
