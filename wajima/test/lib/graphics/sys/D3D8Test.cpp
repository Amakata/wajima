//CUPPA:include=+
#include "graphics/sys/D3D8.h"
#include "graphics/sys/D3DDevice.h"
#include "graphics/sys/DXAssert.h"
#include "graphics/sys/DXException.h"
//CUPPA:include=-
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include "Config.h"

#define	FORMAT	D3DFMT_X8R8G8B8


extern HWND hWnd__;


//CUPPA:namespace=+
namespace zefiro_graphics {
//CUPPA:namespace=-

class D3D8Test : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(D3D8Test);
//CUPPA:suite=+
  CPPUNIT_TEST(testAdapterCount);
  CPPUNIT_TEST(testAdapterModeCount);
  CPPUNIT_TEST(testIsAvailable);
  CPPUNIT_TEST(testGetAdapterVector);
  CPPUNIT_TEST(testCreateDevice);
//CUPPA:suite=-
  CPPUNIT_TEST_SUITE_END();
private:
	D3D8 *d3d8_;
  // your stuff...

public:

  virtual void setUp() { d3d8_ = new zefiro_graphics::D3D8(); }
  virtual void tearDown() { delete d3d8_; }

//CUPPA:decl=+
  void testAdapterCount() {
	CPPUNIT_ASSERT( 0 < d3d8_->getAdapterCount() );
  }
  void testAdapterModeCount() {
	for( int i=0 ; i<d3d8_->getAdapterCount() ; ++i ){
		CPPUNIT_ASSERT( 0 < d3d8_->getAdapterModeCount( i ) );
	}
  }
  void testIsAvailable() {
	std::vector<zefiro_graphics::Adapter> adapters = d3d8_->getAdapterVector();
	CPPUNIT_ASSERT( 0 < adapters.size() );
  }
  void testGetAdapterVector() {
	CPPUNIT_ASSERT_EQUAL( true , d3d8_->isAvailable() );
  }
  void testCreateDevice() {
	try{
		D3DDevice *d3ddevice =  d3d8_->createDevice(  Config::config__->getInteger("graphics_device_num") , getDefaultAdapterMode() ,  Config::config__->getBool("graphics_device_windowmode") , Config::config__->getBool("graphics_device_threaded") , hWnd__ ); 
		delete d3ddevice;
	}catch( zefiro_graphics::DXException &dxe ){
		std::stringstream message;
		message << dxe.what() << " " << dxe.getHResult() <<" "<< getDefaultAdapterMode().toString() << " " << hWnd__;
		CPPUNIT_ASSERT_MESSAGE(message.str(),false);
	}
  }
//CUPPA:decl=-
  Mode getDefaultAdapterMode(){
	std::vector<zefiro_graphics::Adapter> adapters = d3d8_->getAdapterVector();
	std::vector<zefiro_graphics::Mode> modes = adapters[Config::config__->getInteger("graphics_device_num")].getModeVector();
	std::vector<Mode>::iterator end = modes.end();
	for( std::vector<Mode>::iterator current = modes.begin() ; current != end ; ++current ){
		if( current->getWidth() ==  Config::config__->getInteger("graphics_device_width") && current->getHeight() == Config::config__->getInteger("graphics_device_height")&& current->getFormat() == FORMAT ){
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

CPPUNIT_TEST_SUITE_REGISTRATION(D3D8Test);
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(D3D8Test,"zefiro_graphics");

}
