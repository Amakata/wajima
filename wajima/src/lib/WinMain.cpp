/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/Attic/WinMain.cpp,v 1.8 2002/05/25 15:59:05 ama Exp $
 */

#include <fstream>
#include <windows.h>

#include "graphics/sys/D3D8.h"
#include "system/Process.h"
#include "system/Thread.h"
#include "std/Logger.h"

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

class TestRunnable : public zefiro_system::Runnable
{
public:
	virtual void run(){
		zefiro_system::Thread *thread = zefiro_system::Thread::getCurrentThread();
		std::ostringstream ostrstr;
		ostrstr << thread << " " << thread->getThreadID();
		HDC hdc = GetDC( g_hwnd );
		for( int y=0 ; y<320 ; y+=16 ){
			TextOut(hdc,10,y,ostrstr.str().c_str(),ostrstr.str().size());
			zefiro_system::Thread::yield();
		}
		ReleaseDC( g_hwnd , hdc );
	}
};


void ThreadTest(){
	std::ostringstream ostrstr;

	ostrstr << zefiro_system::Thread::getCurrentThread() << " " << zefiro_system::Thread::getCurrentThread()->getThreadID();
	HDC hdc = GetDC( g_hwnd );
	TextOut( hdc , 10, 400 , ostrstr.str().c_str(),ostrstr.str().size());
	ReleaseDC( g_hwnd , hdc );
	zefiro_system::Runnable *r = new TestRunnable();
	zefiro_system::Thread *thread = new zefiro_system::Thread(r,"TestThread");
	thread->setJoinable( true );
	thread->start();
	bool loop = true;
	while(loop){
		try{
			thread->join(1);	//	0‚É‚·‚é‚ÆA‚Æ‚Ü‚ç‚È‚­‚È‚éB
			loop = false;
		}catch( zefiro_system::TimeOutException &toe ){
		}
	}
}


std::ofstream *g_ostr;


LRESULT CALLBACK WndProc( HWND hWnd ,
                                                  UINT message ,
                                                  WPARAM wParam ,
                                                  LPARAM lParam )
{
	zefiro_system::Process *process;
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
			process = new zefiro_system::Process("c:\\windows\\notepad.exe output.txt");
			process->start();
			delete process;
			break;
		case IDM_ADAPTER_DEVICE_OUTPUT:
			AdapterDeviceOutput();
			process = new zefiro_system::Process("c:\\windows\\notepad.exe AdapterDevice.txt");
			process->start();
			delete process;
			break;
		case IDM_THREAD_TEST:
			ThreadTest();
			Sleep(1000);
			process = new zefiro_system::Process("c:\\windows\\notepad.exe logger.txt");
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
