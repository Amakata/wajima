/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/Attic/WinMain.cpp,v 1.10 2002/05/31 19:12:44 ama Exp $
 */

#include <fstream>
#include <windows.h>

#include "graphics/sys/D3D8.h"
#include "system/Process.h"
#include "system/Thread.h"
#include "system/SyncObject.h"
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
	TestRunnable():syncObject_(new zefiro_system::SyncObject()){
	}
	virtual ~TestRunnable(){
		delete syncObject_;
	}
	virtual void notify(){
			syncObject_->notify();
	}
	virtual void run(){
		zefiro_system::Thread *thread = zefiro_system::Thread::getCurrentThread();
		std::ostringstream ostrstr;
		ostrstr << thread << " " << thread->getThreadID();
		HDC hdc = GetDC( g_hwnd );
		for( int y=0 ; y<16 ; y+=16 ){
			TextOut(hdc,10,y,ostrstr.str().c_str(),ostrstr.str().size());
			syncObject_->wait();
		}
		ReleaseDC( g_hwnd , hdc );
	}
protected:
	zefiro_system::SyncObject *syncObject_;
};

class ThreadTest{
public:
	static void create(){
		if( count__ == 0 && !active__ ){
			r__ = new TestRunnable();
			thread__ = new zefiro_system::Thread(r__,"TestThread");
		}
	}
	static void start(){
		if( count__ == 0 && !active__ ){
			thread__->setJoinable( false );
			thread__->start();
			active__ = true;
		}
	}
	static void notify(){
		if( !active__ ){
			return;
		}
		if( count__ < 1 ){
			r__->notify();
			++count__;
		}else{
			count__ = 0;
			active__ = false;
		}
	}
	static bool active__;	//	スレッドが活動中か？
	static int count__;		//	notifyが何回発動したか？
	static TestRunnable *r__;
	static zefiro_system::Thread *thread__;
};

TestRunnable* ThreadTest::r__;
zefiro_system::Thread* ThreadTest::thread__;
int ThreadTest::count__ = 0;
bool ThreadTest::active__ = false;

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
			ThreadTest::create();
			ThreadTest::start();
			Sleep(1000);
			ThreadTest::notify();
			process = new zefiro_system::Process("c:\\windows\\notepad.exe logger.txt");
			process->start();
			delete process;
			break;
		case IDM_THREAD_NOTIFY:
			ThreadTest::notify();
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
