#pragma once

#include "Exception.hpp"
#include <windows.h>
#include <sstream>
#include <dxerr9.h>
#ifdef PSS_STD_DXEXCEPTION_COMPILE
#pragma comment(lib,"dxerr9.lib")
#endif
namespace pss {
	namespace std {
		class DXError{
		public:
			DXError():errorCode_(0){
			}
			DXError( DWORD errorCode ){
				errorCode_ = errorCode;
			}
			::std::string message()const{
				::std::ostringstream ostr;
				switch( errorCode_ ){
				case ERROR_SUCCESS:
					return "SUCCESS";
				default:				
					::std::string name(DXGetErrorString9(errorCode_));
					::std::string description(DXGetErrorDescription9(errorCode_));
					ostr << name << "(" << errorCode_ << ")" << description;
					return ostr.str();
				}
			}
			DWORD getErrorCode()const{
				return errorCode_;
			}
		private:
			DWORD errorCode_;
		};
	}
}
