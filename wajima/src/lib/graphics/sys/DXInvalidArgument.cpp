/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/graphics/sys/DXInvalidArgument.cpp,v 1.3 2002/11/14 16:51:59 ama Exp $
 */

#include "DXInvalidArgument.h"

namespace zefiro_graphics {
	DXInvalidArgument::DXInvalidArgument( std::string message , HRESULT hr , zefiro_std::SourceLine sourceLine )
		:DXException(message , hr,sourceLine){
	}
	DXInvalidArgument::DXInvalidArgument( std::string message , HRESULT hr , long lineNumber , std::string fileName )
		: DXException( message , hr , lineNumber , fileName  ){
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