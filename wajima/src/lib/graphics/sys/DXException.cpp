/**
 * $Header : $
 */

#include "graphics/sys/DXException.h"

namespace zefiro_graphics {
	DXException::DXException( HRESULT hr , zefiro_std::SourceLine sourceLine , std::string additionalMessage)
		: Exception(additionalMessage , sourceLine),_hr(hr){
	}
	DXException::DXException( HRESULT hr , long lineNumber , std::string fileName ,std::string additionalMessage )
		: Exception(additionalMessage,lineNumber,fileName),_hr(hr){
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
