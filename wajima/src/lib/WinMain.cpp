/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/Attic/WinMain.cpp,v 1.15 2002/08/30 09:23:23 ama Exp $
 */

#include <fstream>
#include <windows.h>

#include "graphics/sys/D3D8.h"
#include "system/Process.h"
#include "system/Thread.h"
#include "system/SyncObject.h"
#include "std/Logger.h"
#include "std/sys/Win32Exception.h"

#include "Config.h"
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




class TestRunnable : public zefiro_system::Runnable
{
public:
	TestRunnable( HWND hWnd ):syncObject_(new zefiro_system::SyncObject()),hWnd_(hWnd){
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
		HDC hdc = GetDC( hWnd_ );
		for( int y=0 ; y<16 ; y+=16 ){
			TextOut(hdc,10,y,ostrstr.str().c_str(),ostrstr.str().size());
			syncObject_->wait();
		}
		ReleaseDC( hWnd_ , hdc );
	}
protected:
	zefiro_system::SyncObject *syncObject_;
	HWND hWnd_;
};

class ThreadTest{
public:
	static void create( HWND hWnd ){
		if( count__ == 0 && !active__ ){
			r__ = new TestRunnable( hWnd );
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
	static bool active__;	//	�X���b�h�����������H
	static int count__;		//	notify�����񔭓��������H
	static TestRunnable *r__;
	static zefiro_system::Thread *thread__;
};

TestRunnable* ThreadTest::r__;
zefiro_system::Thread* ThreadTest::thread__;
int ThreadTest::count__ = 0;
bool ThreadTest::active__ = false;


HWND hWnd__ = 0;


class ZefirolibTestApp
{
public:
	ZefirolibTestApp( HWND hWnd ):hWnd_(hWnd){
		hWnd__ = hWnd;
		Config::config__ = new Config("zefirolibtest.ini");
		ostr_.open(Config::config__->getCStr("logfile") );
		zefiro_std::Logger::setOutputter( &ostr_ );
	}
	virtual ~ZefirolibTestApp(){
		delete Config::config__;
		ostr_.close();
		zefiro_std::Logger::resetOutputter();
	}
	void testUnit(){
        std::ofstream ofs;
		ofs.open( Config::config__->getCStr("unittestfile") );
        CppUnit::TextUi::TestRunner runner;        
        runner.addTest( CppUnit::TestFactoryRegistry::getRegistry().makeTest() );
        runner.setOutputter( new CppUnit::TextOutputter(&runner.result(),ofs ) );
        runner.run( "" , true );
        ofs.close();
		exec( Config::config__->getString("editor") + " " + Config::config__->getString("unittestfile") );
	}
	void testGetAdapterDeviceInfo(){
        std::ofstream        ofs;
        ofs.open( Config::config__->getCStr("devicefile") );
        zefiro_graphics::D3D8 *d3d8 = new zefiro_graphics::D3D8();
        std::vector<zefiro_graphics::Adapter> adapters = d3d8->getAdapterVector();
        for( std::vector<zefiro_graphics::Adapter>::iterator adapter = adapters.begin() ; adapter < adapters.end(); ++adapter ){
                 ofs << adapter->toString() << std::endl;
        }
        delete d3d8;
        ofs.close();
		exec( Config::config__->getString("editor") + " " + Config::config__->getString("devicefile") );
	}
	void testThread(){
		ThreadTest::create( hWnd_ );
		ThreadTest::start();
		exec(Config::config__->getString("editor") + " " + Config::config__->getString("logfile") );
	}
	void testThreadNotify(){
		ThreadTest::notify();
	}
protected:
	void exec( std::string cmdLine ){
		zefiro_system::Process *process = new zefiro_system::Process( cmdLine );
		try{
			process->start();
		}catch( zefiro_std::Win32Exception &e ){
			std::string message = std::string(e.what()) + "\n" + cmdLine;
			MessageBox( hWnd_ , message.c_str() , "Error" , MB_OK );
		}
		delete process;
	}
	std::ofstream ostr_;
 	HWND hWnd_;
};


LRESULT CALLBACK WndProc( HWND hWnd ,
                                                  UINT message ,
                                                  WPARAM wParam ,
												  LPARAM lParam )
{
	static ZefirolibTestApp *app;

	switch( message )
    {
	case WM_CREATE:
		app = new ZefirolibTestApp( hWnd );
		break;
	case WM_COMMAND:
		switch( LOWORD(wParam) )
		{
		case IDM_TEST:
			app->testUnit();
			break;
		case IDM_ADAPTER_DEVICE_OUTPUT:
			app->testGetAdapterDeviceInfo();
			break;
		case IDM_THREAD_TEST:
			app->testThread();
			break;
		case IDM_THREAD_NOTIFY:
			app->testThreadNotify();
			break;
		case IDM_EXIT:
			PostMessage( hWnd , WM_CLOSE , 0 , 0 );
			break;
		}
		break;
	case WM_DESTROY:
		delete app;
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		delete app;
		PostQuitMessage(0);
		break;
	default:
		return( DefWindowProc( hWnd , message , wParam , lParam ) );
	}
	return 0L;
}
