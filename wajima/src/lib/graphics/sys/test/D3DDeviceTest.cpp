//CUPPA:include=+
#include "graphics/sys/D3DDevice.h"
#include "graphics/sys/D3D8.h"
//CUPPA:include=-
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <vector>

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

class D3DDeviceTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(D3DDeviceTest);
//CUPPA:suite=+
  CPPUNIT_TEST(testCreateTexture);
//CUPPA:suite=-
  CPPUNIT_TEST_SUITE_END();
private:

  // your stuff...
	D3D8	*d3d8_;
	D3DDevice *device_;
public:

	virtual void setUp() { 
		d3d8_ = new D3D8();
		device_ = d3d8_->createDevice(  DEVICENUMBER , getDefaultAdapterMode() , WINDOWMODE , THREADED , hWnd__ );
	}
  virtual void tearDown() {
	delete device_;
	delete d3d8_;
  }

//CUPPA:decl=+
  void testCreateTexture() {
	  CPPUNIT_FAIL("no implementation");
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

CPPUNIT_TEST_SUITE_REGISTRATION(D3DDeviceTest);
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(D3DDeviceTest,"zefiro_graphics");

}
