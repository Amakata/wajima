#pragma once

#include <windows.h>
#include <string>
#include <sstream>
#include "pss/std/Win32Exception.hpp"

namespace pss {
	namespace system {
		class Win32Event{
		public:
			Win32Event( bool initState =false , bool manualReset = true , ::std::string name = "" );
			virtual ~Win32Event();
			bool isAlreadyExist() const;
			bool isAvailable() const;
			::std::string getName() const;
			void set();
			void reset();
			void pulse();
			bool wait( long milliseconds = INFINITE );
			::std::string toString() const;
			HANDLE getHandle()const{
				return event_;
			}
		protected:
			Win32Event( const Win32Event &event );
			Win32Event &operator=( const Win32Event &other );
			HANDLE	event_;
			::std::string name_;
			bool	manualReset_;
			bool	exist_;
			DWORD	constructError_;
		};
	}
}

#ifdef PSS_SYSTEM_WIN32EVENT_COMPILE
namespace pss {
	namespace system {
		Win32Event::Win32Event( bool initState  , bool manualReset , ::std::string name )
			:manualReset_(manualReset),name_(name),exist_(false),constructError_(0){
			if( name_ == ::std::string("") ){
				event_ = CreateEvent( NULL , manualReset , initState , NULL );
			}else{
				event_ = CreateEvent( NULL , manualReset , initState , name_.c_str() );
			}
			if( event_ == NULL ){
				constructError_ = GetLastError();
				return;
			}
			if( GetLastError() == ERROR_ALREADY_EXISTS ){
				exist_ = true;
			}
		}
		Win32Event::~Win32Event(){
			if( isAvailable() ){
				CloseHandle( event_ );
			}
		}
		bool Win32Event::isAlreadyExist() const{
			return exist_;
		}
		bool Win32Event::isAvailable() const{
			return event_ != NULL;
		}
		::std::string Win32Event::getName() const{
			return name_;
		}
		void Win32Event::set() {
			if( isAvailable() ){
				if( 0 == SetEvent( event_ ) ){
					PSS_THROW_PARAM1( ::pss::std::Win32Error(GetLastError()) , "");
				}
			}else{
				PSS_THROW_PARAM1( ::pss::std::Win32Error(constructError_) , "");
			}
		}
		void Win32Event::reset() {
			if( isAvailable() ){
				if( 0 == ResetEvent( event_ ) ){
					PSS_THROW_PARAM1( ::pss::std::Win32Error(GetLastError()) , "");
				}
			}else{
				PSS_THROW_PARAM1( ::pss::std::Win32Error(constructError_) , "");
			}
		}
		void Win32Event::pulse() {
			if( isAvailable() ){
				if( 0 == PulseEvent( event_ ) ){
					PSS_THROW_PARAM1( ::pss::std::Win32Error(GetLastError()) , "");
				}
			}else{
				PSS_THROW_PARAM1( ::pss::std::Win32Error(constructError_) , "");
			}
		}
		bool Win32Event::wait( long milliseconds ) {
			if( isAvailable() ){
				DWORD result = WaitForSingleObject( event_ , milliseconds );
				switch( result ){
				case WAIT_TIMEOUT:
					// タイムアウトによるリターン
					return false;
				case WAIT_OBJECT_0:
					// 正常にwaitから解放された。
					return true;
				case WAIT_ABANDONED:
					// 所有権が放棄されたeventだった。
					return true;
				case WAIT_FAILED:
					PSS_THROW_PARAM1( ::pss::std::Win32Error(GetLastError()) , "");
				default:
					// 不明なエラー
					PSS_THROW_PARAM1( ::pss::std::Win32Error(GetLastError()) , "");
				}
				return false;
			}else{
				//	eventオブジェクト生成時のエラー
				PSS_THROW_PARAM1( ::pss::std::Win32Error(constructError_) , "");
				return false;
			}
		}
		::std::string Win32Event::toString() const {
			::std::ostringstream ostrstr;
			ostrstr << " Event Handle = "  << event_ << " , Event Name = " << name_ << " , Manual Reset = " << manualReset_ << " , Already Exist = " << exist_;
			return ostrstr.str();
		}
	}
}
#endif