#pragma once
#include <string>
#include <windows.h>
#include "pss/std/Win32Exception.hpp"

namespace pss {
	namespace system {
		class Process
		{
		public:
			Process( ::std::string cmdLine );
			virtual ~Process();
			void start();
		protected:
			::std::string _cmdLine;
			HANDLE _process;
			DWORD _processID;
		};
#ifdef PSS_SYSTEM_PROCESS_COMPILE
		Process::Process( ::std::string cmdLine ):_cmdLine(cmdLine),_process(NULL),_processID(0){
		}
		Process::~Process(){
		}
		void Process::start(){
			PROCESS_INFORMATION processInformation;
			STARTUPINFO	startupInfo;
			memset( &startupInfo , 0 , sizeof(startupInfo) );
			startupInfo.cb = sizeof(startupInfo);
			if( 0 == CreateProcess(NULL,const_cast<char*>(_cmdLine.c_str()),NULL,NULL,FALSE,0,NULL,NULL, &startupInfo , &processInformation ) ){
				PSS_THROW_PARAM1( ::pss::std::Win32Error(GetLastError()) , "");
			}
			_process = processInformation.hProcess;
			_processID = processInformation.dwProcessId;
		}
#endif
	}
}
