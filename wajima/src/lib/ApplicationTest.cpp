

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
#include <mmsystem.h>
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
	zefiro_graphics::D3DTexture *tex[4];
	zefiro_graphics::D3D8 *d3d8 = new zefiro_graphics::D3D8();
	zefiro_graphics::D3DDevice *device = d3d8->createDevice(
													0 ,
													zefiro_graphics::Mode(
														Config::config__->getInteger("graphics_device_width") ,
														Config::config__->getInteger("graphics_device_height") ,
														0 ,
														D3DFMT_X8R8G8B8
													) , 
													Config::config__->getBool("graphics_device_windowmode") ,
													Config::config__->getBool("graphics_device_threaded"),
													hWnd_ 
												);
	zefiro_graphics::D3DFont *font = device->createFont( 16 , 32 , "ＭＳ Ｐゴシック" );
	
	tex[0] = device->loadTexture( Config::config__->getString("graphics_texture_filename_red") );
	tex[1] = device->loadTexture( Config::config__->getString("graphics_texture_filename_green") );
	tex[2]= device->loadTexture( Config::config__->getString("graphics_texture_filename_blue") );
	tex[3] = device->loadTexture( Config::config__->getString("graphics_texture_filename_box") );

	int width = Config::config__->getInteger("graphics_device_width");
	int height = Config::config__->getInteger("graphics_device_height");
	int maxI = Config::config__->getInteger("graphics_texture_render_number_i");
	int maxJ = Config::config__->getInteger("graphics_texture_render_number_j");

	DWORD now = 0 , old = 0;        // 時間計測に使う
	INT FrameCount = 0;        // フレーム・カウンタ

	for( int i=0 ; i<maxI ; ++i ){
		device->clear();
		device->renderBegin();
		for( int j=0 ; j<maxJ ; ++j ){
			for( int k=0 ; k<4 ; ++k ){
				device->render( tex[k] , k * 100.0f , 0.0f , 0.0f );
			}
		}
	
		std::ostringstream oss;
		if(FrameCount <= 0){
			old = now;
			now = timeGetTime();
			FrameCount = 100;
		}
		oss << 100.0f / (now - old) * 1000;
		FrameCount--;
		font->draw(oss.str(),0,0,100,32,0xFF0000FF);
		device->renderEnd();
	}
	for( int k=0 ; k<4 ; ++k ){
		delete tex[k];
	}
	delete font;
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

