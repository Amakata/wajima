/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/Attic/WinMain.cpp,v 1.3 2002/05/20 18:35:06 ama Exp $
 */

#include <fstream>
#include <windows.h>

#include <graphics/sys/D3D8.h>
#include <thread/Thread.h>
#include <std/Logger.h>

#include "WindowClass.h"
#include "Window.h"
#include "resource.h"


#include <cppunit/TextTestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TextOutputter.h>


LRESULT CALLBACK WndProc( HWND hWnd ,
                                                  UINT message ,
                                                  WPARAM wParam ,
                                                  LPARAM lParam );


int APIENTRY WinMain( HINSTANCE hInstance ,
                                         HINSTANCE hPrevInstance , 
                                         LPSTR lpCmdLine ,
                                         int nShowCmd )
{

        if( !hPrevInstance ){
			zefiro_stdtest::WindowClass *windowClass = new zefiro_stdtest::WindowClass( hInstance , WndProc ,"TestApp");
                windowClass->registerClass();
                delete windowClass;
        }
        zefiro_stdtest::Window *window = new zefiro_stdtest::Window( hInstance , "TestApp" , "TestApplicationWindow");
        window->show(nShowCmd);

        MSG        msg;
        while( GetMessage( &msg , NULL , 0 , 0 ) ){
                TranslateMessage( &msg );
                DispatchMessage( &msg );
        }
//      delete window;
        return( msg.wParam );
}

void UnitTest(){
        std::ofstream        ofs;
        ofs.open("output.txt");
        CppUnit::TextUi::TestRunner runner;        
        runner.addTest( CppUnit::TestFactoryRegistry::getRegistry().makeTest() );
        runner.setOutputter( new CppUnit::TextOutputter(&runner.result(),ofs ) );
        runner.run( "" , true );
        ofs.close();
}

void AdapterDeviceOutput(){
        std::ofstream        ofs;
        ofs.open("AdapterDevice.txt");
        zefiro_graphics::D3D8 *d3d8 = new zefiro_graphics::D3D8();
        std::vector<zefiro_graphics::Adapter> adapters = d3d8->getAdapterVector();
        for( std::vector<zefiro_graphics::Adapter>::iterator adapter = adapters.begin() ; adapter < adapters.end(); ++adapter ){
                 ofs << adapter->toString() << std::endl;
        }
        delete d3d8;
        ofs.close();
}

HWND g_hwnd;

class TestRunnable : public zefiro_thread::Runnable
{
public:
	virtual void run(){
		zefiro_thread::Thread *thread = zefiro_thread::Thread::getCurrentThread();
		std::ostringstream ostrstr;
		ostrstr << thread << " " << thread->getThreadID();
		HDC hdc = GetDC( g_hwnd );
		for( int y=0 ; y<320 ; y+=16 ){
			TextOut(hdc,10,y,ostrstr.str().c_str(),ostrstr.str().size());
			zefiro_thread::Thread::yield();
		}
		ReleaseDC( g_hwnd , hdc );
	}
};


void ThreadTest(){
	zefiro_thread::Runnable *r = new TestRunnable();
	zefiro_thread::Thread *thread = new zefiro_thread::Thread(r);
	thread->setJoinable( false );
	thread->start();
}

class Process
{
public:
	Process( std::string cmdLine ):_cmdLine(cmdLine),_process(NULL),_processID(0){
	}
	virtual ~Process(){
	}
	void start(){
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
protected:
	std::string _cmdLine;
	HANDLE _process;
	DWORD _processID;
};


std::ofstream *g_ostr;


LRESULT CALLBACK WndProc( HWND hWnd ,
                                                  UINT message ,
                                                  WPARAM wParam ,
                                                  LPARAM lParam )
{
	Process *process;
	switch( message )
    {
	case WM_CREATE:
		g_hwnd = hWnd;
		g_ostr = new std::ofstream("logger.txt");
		zefiro_std::Logger::setOutputter( g_ostr );
		break;
	case WM_COMMAND:
		switch( LOWORD(wParam) )
		{
		case IDM_TEST:
			UnitTest();
			process = new Process("c:\\windows\\notepad.exe output.txt");
			process->start();
			delete process;
			break;
		case IDM_ADAPTER_DEVICE_OUTPUT:
			AdapterDeviceOutput();
			process = new Process("c:\\windows\\notepad.exe AdapterDevice.txt");
			process->start();
			delete process;
			break;
		case IDM_THREAD_TEST:
			ThreadTest();
			Sleep(1000);
			process = new Process("c:\\windows\\notepad.exe logger.txt");
			process->start();
			delete process;
			break;
		case IDM_EXIT:
			PostMessage( hWnd , WM_CLOSE , 0 , 0 );
			break;
		}
		break;
	case WM_DESTROY:
		g_ostr->close();
		zefiro_std::Logger::resetOutputter();
		delete g_ostr;
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		g_ostr->close();
		zefiro_std::Logger::resetOutputter();
		delete g_ostr;
		PostQuitMessage(0);
		break;
	default:
		return( DefWindowProc( hWnd , message , wParam , lParam ) );
	}
	return 0L;
}
