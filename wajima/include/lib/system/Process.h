/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/include/lib/system/Attic/Process.h,v 1.2 2002/05/25 15:58:21 ama Exp $
 */

#ifndef __PROCESS_H__
#define __PROCESS_H__

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