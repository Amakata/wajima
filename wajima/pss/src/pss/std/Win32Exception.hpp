#pragma once

#include "Exception.hpp"
#include <windows.h>
#include <sstream>

namespace pss {
	namespace std {
		class Win32Error{
		public:
			Win32Error():errorCode_(0){
			}
			Win32Error( DWORD errorCode ){
				errorCode_ = errorCode;
			}
			::std::string message()const{
				char *tcMessage;
				if( 0 == FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS |FORMAT_MESSAGE_FROM_SYSTEM , NULL , errorCode_ , MAKELANGID(LANG_JAPANESE,  SUBLANG_ENGLISH_US),(LPTSTR)&tcMessage , 0 , NULL ) ){
					PSS_THROW_PARAM1( ::pss::std::Win32Error(GetLastError()) , "ívñΩìIÇ»ÉGÉâÅ[" );	
				}
				return ::std::string( tcMessage );
			}
			DWORD getErrorCode()const{
				return errorCode_;
			}
		private:
			DWORD errorCode_;
		};
	}
}

