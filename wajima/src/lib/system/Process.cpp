/**
 * $ Header: $
 */

#include "system/Process.h"
#include "std/sys/Win32Assert.h"

namespace zefiro_system {
	Process::Process( std::string cmdLine ):_cmdLine(cmdLine),_process(NULL),_processID(0){
	}
	Process::~Process(){
	}
	void Process::start(){
		PROCESS_INFORMATION processInformation;
		STARTUPINFO	startupInfo;
		memset( &startupInfo , 0 , sizeof(startupInfo) );
		startupInfo.cb = sizeof(startupInfo);
		if( 0 == CreateProcess(NULL,const_cast<char*>(_cmdLine.c_str()),NULL,NULL,FALSE,0,NULL,NULL, &startupInfo , &processInformation ) ){
			WIN32ASSERT( GetLastError() );
		}
		_process = processInformation.hProcess;
		_processID = processInformation.dwProcessId;
	}
};