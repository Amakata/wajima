/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/include/lib/system/sys/Attic/Win32Event.h,v 1.2 2002/05/25 15:58:29 ama Exp $
 */

#ifndef __WIN32EVENT_H__
#define __WIN32EVENT_H__

#include <windows.h>
#include <string>

namespace zefiro_system {
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
		std::string toString() const;
	protected:
		Win32Event( const Win32Event &event );
		Win32Event &operator=( const Win32Event &other );
		HANDLE	event_;
		std::string name_;
		bool	manualReset_;
		bool	exist_;
		DWORD	constructError_;
	};
};

#endif //__WIN32EVENT_H__