/**
 * $Header : $
 */

#include "DXInvalidArgument.h"

namespace zefiro_graphics {
	DXInvalidArgument::DXInvalidArgument( HRESULT hr , zefiro_std::SourceLine sourceLine , std::string additionalMessage )
		:DXException(hr,sourceLine,additionalMessage){
	}
	DXInvalidArgument::DXInvalidArgument( HRESULT hr , long lineNumber , std::string fileName ,std::string additionalMessage )
		: DXException( hr , lineNumber , fileName , additionalMessage ){
	}
	DXInvalidArgument::DXInvalidArgument( const DXInvalidArgument &other ):DXException(other){
	}
	DXInvalidArgument::~DXInvalidArgument() throw(){
	}
	DXInvalidArgument &DXInvalidArgument::operator =( const DXInvalidArgument &other ){
		DXException::operator =(other);
		return *this;
	}
	zefiro_std::Exception *DXInvalidArgument::clone() const{
		return new DXInvalidArgument( *this );
	}
	bool DXInvalidArgument::isInstanceOf( const zefiro_std::Exception::Type &exceptionType ) const{
	     return exceptionType == type()  ||
         DXException::isInstanceOf( exceptionType ) ||
		 InvalidArgument::isInstanceOf( exceptionType );
	}
	zefiro_std::Exception::Type DXInvalidArgument::type(){
		return zefiro_std::Exception::Type( "zefiro_graphics::DXInvalidArgument" );
	}

};