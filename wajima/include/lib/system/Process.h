#ifndef __PROCESS_H__
#define __PROCESS_H__

/**
 * $ Header: $
 */

#include <string>
#include <windows.h>

namespace zefiro_system {
	class Process
	{
	public:
		Process( std::string cmdLine );
		virtual ~Process();
		void start();
	protected:
		std::string _cmdLine;
		HANDLE _process;
		DWORD _processID;
	};
};

#endif //__PROCESS_H__