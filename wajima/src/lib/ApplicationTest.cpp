

#include "ApplicationTest.h"

#include "graphics/sys/D3D8.h"
#include "graphics/sys/D3DDevice.h"
#include "graphics/sys/D3DTexture.h"
#include "system/Process.h"
#include "std/Logger.h"
#include "Config.h"
#include "ThreadTest.h"
#include <cppunit/TextTestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TextOutputter.h>
#include <stdlib.h>

HWND hWnd__ = 0;

ApplicationTest::ApplicationTest( HWND hWnd ):hWnd_(hWnd){
	hWnd__ = hWnd;
	Config::config__ = new Config("zefirolibtest.ini");
	ostr_.open(Config::config__->getCStr("logfile") );
	zefiro_std::Logger::setOutputter( &ostr_ );
}
ApplicationTest::~ApplicationTest(){
	delete Config::config__;
	ostr_.close();
	zefiro_std::Logger::resetOutputter();
}
void ApplicationTest::testUnit(){
	std::ofstream ofs;
	ofs.open( Config::config__->getCStr("unittestfile") );
    CppUnit::TextUi::TestRunner runner;        
    runner.addTest( CppUnit::TestFactoryRegistry::getRegistry().makeTest() );
    runner.setOutputter( new CppUnit::TextOutputter(&runner.result(),ofs ) );
    runner.run( "" , true );
    ofs.close();
	exec( Config::config__->getString("editor") + " " + Config::config__->getString("unittestfile") );
}
void ApplicationTest::testGetAdapterDeviceInfo(){
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
void ApplicationTest::demoDirectX(){
	zefiro_graphics::D3DTexture *texBlue,*texRed,*texGreen,*texBox;
	zefiro_graphics::D3D8 *d3d8 = new zefiro_graphics::D3D8();
	zefiro_graphics::D3DDevice *device = d3d8->createDevice( 0 , zefiro_graphics::Mode(800,600,0,D3DFMT_X8R8G8B8) ,false,  false , hWnd_ );
	texRed = device->loadTexture( Config::config__->getString("graphics_texture_filename_red") );
	texGreen = device->loadTexture( Config::config__->getString("graphics_texture_filename_green") );
	texBlue= device->loadTexture( Config::config__->getString("graphics_texture_filename_blue") );
	texBox = device->loadTexture( Config::config__->getString("graphics_texture_filename_box") );

	for( int i=0 ; i<100 ; ++i ){
		device->clear();
		device->renderBegin();
		for( int i=0 ; i<1000 ; ++i ){
			device->render( texRed , (float)rand()/(float)RAND_MAX *700  , (float)rand()/(float)RAND_MAX *700 , i/1000.0f );
			device->render( texGreen , (float)rand()/(float)RAND_MAX *700 , (float)rand()/(float)RAND_MAX *700 , i/1000.0f);
			device->render( texBlue , (float)rand()/(float)RAND_MAX *700, (float)rand()/(float)RAND_MAX *700 , i/1000.0f);
			device->render( texBox , (float)rand()/(float)RAND_MAX *700 , (float)rand()/(float)RAND_MAX *700 , i/1000.0f);
		}
		device->renderEnd();
	}
	delete texRed;
	delete texBlue;
	delete texGreen;
	delete texBox;
	delete device;
	delete d3d8;
}
void ApplicationTest::testThread(){
	ThreadTest::create( hWnd_ );
	ThreadTest::start();
	exec(Config::config__->getString("editor") + " " + Config::config__->getString("logfile") );
}
void ApplicationTest::testThreadNotify(){
	ThreadTest::notify();
}

void ApplicationTest::exec( std::string cmdLine ){
	zefiro_system::Process *process = new zefiro_system::Process( cmdLine );
	try{
		process->start();
	}catch( zefiro_std::Win32Exception &e ){
		std::string message = std::string(e.what()) + "\n" + cmdLine;
		MessageBox( hWnd_ , message.c_str() , "Error" , MB_OK );
	}
	delete process;
}

