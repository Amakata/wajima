/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/std/UniqueNumberBadAlloc.cpp,v 1.2 2002/04/28 13:31:40 ama Exp $
 */

#include <std/UniqueNumberBadAlloc.h>

namespace zefiro_std {
	UniqueNumberBadAlloc::UniqueNumberBadAlloc( std::string message , long lineNumber , std::string fileName )
		:zefiro_std::Exception(message,lineNumber,fileName){
	}
	Exception *UniqueNumberBadAlloc::clone() const{
		return new UniqueNumberBadAlloc( *this );
	}
	UniqueNumberBadAlloc & UniqueNumberBadAlloc::operator= (const UniqueNumberBadAlloc& other ){
		*this = other;
		return *this;
	}
	bool UniqueNumberBadAlloc::isInstanceOf( const Exception::Type &type ) const{
		return ( UniqueNumberBadAlloc::getType() == type );
	}
	Exception::Type UniqueNumberBadAlloc::getType(){
		return Exception::Type("zefiro_std::UniqueNumberBadAlloc");
	}
};