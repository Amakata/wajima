/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/std/UniqueNumberBadAlloc.h,v 1.1 2002/11/03 09:05:09 ama Exp $
 */

#ifndef __UNIQUENUMBERBADALLOC_H__
#define __UNIQUENUMBERBADALLOC_H__

#include <string>

#include "std/Exception.h"

namespace zefiro_std {
	/**
	 * ユニークナンバーの割り当てエラー
	 * ユニークナンバーの割り当て資源を使いきり、割り当てられないときに発生する。
	 */
	class UniqueNumberBadAlloc : public zefiro_std::Exception
	{
	public:

		UniqueNumberBadAlloc( std::string message="A unique number is not assigned." , long lineNumber =  UNKNOWNLINENUMBER , std::string fileName = UNKNOWNFILENAME );
		virtual Exception *clone() const;
		UniqueNumberBadAlloc & operator= (const UniqueNumberBadAlloc& other );
		virtual bool isInstanceOf( const Exception::Type &type ) const;
		static Exception::Type getType();		
	};
};

#endif //__UNIQUENUMBERBADALLOC_H__