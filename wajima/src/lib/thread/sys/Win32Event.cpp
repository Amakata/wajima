/**
 * $ Header: $
 */


#include <std/Assert.h>
#include <std/sys/Win32Assert.h>
#include "thread/sys/Win32Event.h"


namespace zefiro_thread {
	Win32Event::Win32Event( bool initState  , bool manualReset , std::string name )
		:_manualReset(manualReset),_name(name),_exist(false),_constructErrorCode(0){
		if( _name == std::string("") ){
			_event = CreateEvent( NULL , manualReset , initState , NULL );
		}else{
			_event = CreateEvent( NULL , manualReset , initState , _name.c_str() );
		}
		if( _event == NULL ){
			_constructErrorCode = GetLastError();
			return;
		}
		if( GetLastError() == ERROR_ALREADY_EXISTS ){
			_exist = true;
		}
	}
	Win32Event::~Win32Event(){
		if( isAvailable() ){
			CloseHandle( _event );
		}
	}
	bool Win32Event::isAlreadyExist() const{
		return _exist;
	}
	bool Win32Event::isAvailable() const{
		return _event != NULL;
	}
	std::string Win32Event::getName() const{
		return _name;
	}
	void Win32Event::set() {
		if( isAvailable() ){
			if( 0 == SetEvent( _event ) ){
				WIN32ASSERT(GetLastError());
			}
		}else{
			WIN32ASSERT( _constructErrorCode );
		}
	}
	void Win32Event::reset() {
		if( isAvailable() ){
			if( 0 == ResetEvent( _event ) ){
				WIN32ASSERT(GetLastError());
			}
		}else{
			WIN32ASSERT( _constructErrorCode );
		}
	}
	void Win32Event::pulse() {
		if( isAvailable() ){
			if( 0 == PulseEvent( _event ) ){
				WIN32ASSERT(GetLastError());
			}
		}else{
			WIN32ASSERT( _constructErrorCode );
		}
	}
	bool Win32Event::wait( long milliseconds ) {
		if( isAvailable() ){
			DWORD result = WaitForSingleObject( _event , milliseconds );
			switch( result ){
			case WAIT_TIMEOUT:
				return false;
			case WAIT_OBJECT_0:
				return true;
			case WAIT_ABANDONED:
				// 所有権が放棄されたeventだった。
				return true;
			case WAIT_FAILED:
				WIN32ASSERT( GetLastError() );
				break;
			default:
				// 不明なエラー
				WIN32ASSERT( GetLastError() );
				break;
			}
			return false;
		}else{
			//	eventオブジェクト生成時のエラー
			WIN32ASSERT( _constructErrorCode );
			return false;
		}
	}
};