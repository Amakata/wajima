/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/graphics/test/Attic/WinMain.cpp,v 1.4 2002/04/28 13:33:01 ama Exp $
 */

#include <fstream>
#include <windows.h>

#include <graphics/sys/D3D8.h>

#include <graphics/test/WindowClass.h>
#include <graphics/test/Window.h>
#include <graphics/test/resource.h>

#include <cppunit/TextTestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
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
	runner.setOutputter( new CppUnit::TextOutputter(&runner.result(),ofs ) );
	runner.run( "" , true );
	ofs.close();
}

void AdapterDeviceOutput(){
	std::ofstream	ofs;
	ofs.open("AdapterDevice.txt");
	zefiro_graphics::D3D8 *d3d8 = new zefiro_graphics::D3D8();
	std::vector<zefiro_graphics::Adapter> adapters = d3d8->getAdapterVector();
	for( std::vector<zefiro_graphics::Adapter>::iterator adapter = adapters.begin() ; adapter < adapters.end(); ++adapter ){
		 ofs << adapter->toString() << std::endl;
	}
	delete d3d8;
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
		case IDM_ADAPTER_DEVICE_OUTPUT:
			AdapterDeviceOutput();
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


