/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/std/test/Attic/WinMain.cpp,v 1.3 2002/04/28 13:31:47 ama Exp $
 */

#include <fstream>
#include <windows.h>

#include <std/test/WindowClass.h>
#include <std/test/Window.h>
#include <std/test/resource.h>
#include <std/test/UniqueNumberFactoryTest.h>

#include <cppunit/TextTestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>

using namespace zefiro_stdtest;

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
		WindowClass *windowClass = new WindowClass( hInstance , WndProc ,"TestApp");
		windowClass->registerClass();
		delete windowClass;
	}
	Window *window = new Window( hInstance , "TestApp" , "TestApplicationWindow");
	window->show(nShowCmd);

	MSG	msg;
	while( GetMessage( &msg , NULL , 0 , 0 ) ){
		TranslateMessage( &msg );
		DispatchMessage( &msg );
	}
//	delete window;
	return( msg.wParam );
}

void UnitTest(){
	std::ofstream	ofs;
	ofs.open("output.txt");
	CppUnit::TextUi::TestRunner runner;	
	runner.addTest( CppUnit::TestFactoryRegistry::getRegistry().makeTest() );
	runner.setOutputter( new CppUnit::TextOutputter(&runner.result(),ofs) );
	runner.run( "" , true );
	ofs.close();
}

LRESULT CALLBACK WndProc( HWND hWnd ,
						  UINT message ,
						  WPARAM wParam ,
						  LPARAM lParam )
{
	switch( message )
	{
	case WM_COMMAND:
		switch( LOWORD(wParam) )
		{
		case IDM_TEST:
			UnitTest();
			PostQuitMessage(0);
			break;
		case IDM_EXIT:
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return( DefWindowProc( hWnd , message , wParam , lParam ) );
	}
	return 0L;
}


