/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/std/UniqueNumberBadAlloc.cpp,v 1.4 2002/09/18 14:46:25 ama Exp $
 */

#include "std/UniqueNumberBadAlloc.h"

namespace zefiro_std {
	UniqueNumberBadAlloc::UniqueNumberBadAlloc( std::string message , long lineNumber , std::string fileName )
		:zefiro_std::Exception(message,lineNumber,fileName){
	}
	Exception *UniqueNumberBadAlloc::clone() const{
		return new UniqueNumberBadAlloc( *this );
	}
	bool UniqueNumberBadAlloc::isInstanceOf( const Exception::Type &type ) const{
		return ( UniqueNumberBadAlloc::getType() == type );
	}
	Exception::Type UniqueNumberBadAlloc::getType(){
		return Exception::Type("zefiro_std::UniqueNumberBadAlloc");
	}
};