//CUPPA:include=+
#include "graphics/sys/D3D8.h"
#include "graphics/sys/D3DDevice.h"
#include "graphics/sys/DXAssert.h"
#include "graphics/sys/DXException.h"
//CUPPA:include=-
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#define DEVICENUMBER 0
#define HEIGHT 600
#define WIDTH 800
#define REFRESHRATE	0
#define	FORMAT	D3DFMT_X8R8G8B8
#define WINDOWMODE false
#define THREADED true


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
		D3DDevice *d3ddevice =  d3d8_->createDevice(  DEVICENUMBER , getDefaultAdapterMode() , WINDOWMODE , THREADED , hWnd__ ); 
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
	std::vector<zefiro_graphics::Mode> modes = adapters[0].getModeVector();
	std::vector<Mode>::iterator end = modes.end();
	for( std::vector<Mode>::iterator current = modes.begin() ; current != end ; ++current ){
		if( current->getWidth() == WIDTH && current->getHeight() == HEIGHT && current->getFormat() == FORMAT ){
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
