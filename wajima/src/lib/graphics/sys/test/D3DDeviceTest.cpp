//CUPPA:include=+
#include "graphics/sys/D3DDevice.h"
#include "graphics/sys/D3D8.h"
//CUPPA:include=-
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <vector>
#include "Config.h"

#define	FORMAT	D3DFMT_X8R8G8B8

extern HWND hWnd__;

//CUPPA:namespace=+
namespace zefiro_graphics {
//CUPPA:namespace=-

class D3DDeviceTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(D3DDeviceTest);
//CUPPA:suite=+
  CPPUNIT_TEST(testCreateTexture);
  CPPUNIT_TEST(testRenderTexture);
  CPPUNIT_TEST(testClear);
//CUPPA:suite=-
  CPPUNIT_TEST_SUITE_END();
private:

  // your stuff...
	D3D8	*d3d8_;
	D3DDevice *device_;
public:

	virtual void setUp() { 
		d3d8_ = new D3D8();
		device_ = d3d8_->createDevice(  Config::config__->getInteger("graphics_device_num") , getDefaultAdapterMode() , Config::config__->getBool("graphics_device_windowmode") , Config::config__->getBool("graphics_device_threaded") , hWnd__ );
	}
	virtual void tearDown() {
		delete device_;
		delete d3d8_;
	}

//CUPPA:decl=+
	void testCreateTexture() {
		D3DTexture *texture;
		texture = device_->loadTexture( Config::config__->getString("graphics_texture_filename") );
		delete texture;
	}
	void testRenderTexture() {
		D3DTexture *texBlue,*texRed,*texGreen,*texBox;
		texRed = device_->loadTexture( Config::config__->getString("graphics_texture_filename_red") );
		texGreen = device_->loadTexture( Config::config__->getString("graphics_texture_filename_green") );
		texBlue= device_->loadTexture( Config::config__->getString("graphics_texture_filename_blue") );
		texBox = device_->loadTexture( Config::config__->getString("graphics_texture_filename_box") );

		device_->clear();
		device_->renderBegin();
		device_->render( texRed , 200.0f , 200.0f , 0.0f);
		device_->render( texGreen , 250.0f , 250.0f , 0.2f);
		device_->render( texBlue , 290.0f , 290.0f , 0.1f);
		device_->render( texBox , 300.0f , 300.0f , 0.3f);
		device_->renderEnd();
		Sleep( 2000 );
		delete texRed;
		delete texBlue;
		delete texGreen;
		delete texBox;
	}
  void testClear() {
		device_->clear();
  }
//CUPPA:decl=-
  Mode getDefaultAdapterMode(){
	std::vector<zefiro_graphics::Adapter> adapters = d3d8_->getAdapterVector();
	std::vector<zefiro_graphics::Mode> modes = adapters[Config::config__->getInteger("graphics_device_num")].getModeVector();
	std::vector<Mode>::iterator end = modes.end();
	for( std::vector<Mode>::iterator current = modes.begin() ; current != end ; ++current ){
		if( current->getWidth() ==  Config::config__->getInteger("graphics_device_width") && current->getHeight() == Config::config__->getInteger("graphics_device_height") && current->getFormat() == FORMAT ){
			return *current;
		}
	}
	return Mode(0,0,0,D3DFMT_X8R8G8B8);
  }
};

}

namespace zefiro_graphics {
//CUPPA:impl=+
//CUPPA:impl=-

CPPUNIT_TEST_SUITE_REGISTRATION(D3DDeviceTest);
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(D3DDeviceTest,"zefiro_graphics");

}
