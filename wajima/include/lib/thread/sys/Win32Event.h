#ifndef __WIN32EVENT_H__
#define __WIN32EVENT_H__

#include <windows.h>
#include <string>

namespace zefiro_thread {
	class Win32Event{
	public:
		Win32Event( bool initState =false , bool manualReset = true , std::string name = "" );
		virtual ~Win32Event();
		bool isAlreadyExist() const;
		bool isAvailable() const;
		std::string getName() const;
		void set();
		void reset();
		void pulse();
		bool wait( long milliseconds = INFINITE );
	protected:
		Win32Event( const Win32Event &event );
		Win32Event &operator=( const Win32Event &other );
		HANDLE	_event;
		std::string _name;
		bool	_manualReset;
		bool	_exist;
		DWORD	_constructErrorCode;
	};
};

#endif //__WIN32EVENT_H__