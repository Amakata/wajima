#ifndef __UNIQUENUMBERBADALLOC_H__
#define __UNIQUENUMBERBADALLOC_H__

#include <std/Exception.h>
#include <string>

namespace zefiro_std {
	/**
	 * ユニークナンバーの割り当てエラー
	 * ユニークナンバーの割り当て資源を使いきり、割り当てられないときに発生する。
	 */
	class UniqueNumberBadAlloc : public zefiro_std::Exception
	{
	public:

		UniqueNumberBadAlloc(const std::string& what_arg="A unique number is not assigned."){
			_what_arg = what_arg;
		}
		virtual const char *what() const throw(){
			return _what_arg.c_str();
		}
	protected:
		std::string _what_arg;
	};
};

#endif //__UNIQUENUMBERBADALLOC_H__