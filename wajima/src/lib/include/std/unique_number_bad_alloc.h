#ifndef __UNIQUE_NUMBER_BAD_ALLOC_H__
#define __UNIQUE_NUMBER_BAD_ALLOC_H__

#include <exception>
#include <string>

namespace zefiro_std {
	/**
	 * ユニークナンバーの割り当てエラー
	 * ユニークナンバーの割り当て資源を使いきり、割り当てられないときに発生する。
	 */
	class unique_number_bad_alloc : public std::exception
	{
	public:
		unique_number_bad_alloc(const std::string& what_arg="A unique number is not assigned."){
			_what_arg = what_arg;
		}
		virtual const char *what() const throw(){
			return _what_arg.c_str();
		}
	protected:
		std::string _what_arg;
	};
};

#endif //__UNIQUE_NUMBER_BAD_ALLOC_H__