#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
//CUPPA:include=+
#include "SmartPtr.h"
#include "graphics/GraphicsManager.h"
#include "graphics/GraphicsDevice.h"
#include "std/Exception.h"
#include "Config.h"
//CUPPA:include=-

class GraphicsDeviceTest : public CppUnit::TestFixture {
//CUPPA:usercode=+

private:
	// your staff
public:
	virtual void setUp() {
		// initialize
	}
	virtual void tearDown() {
		// terminate
	}
//CUPPA:usercode=-

//CUPPA:decl=+
    void test_present() {
		zefiro_graphics::GraphicsManager::GM gm;
		zefiro_graphics::GraphicsDevice::GD gd;
		try{
			gm = zefiro_graphics::GraphicsManager::createGM( Config::getHWND() );
		}catch( zefiro_std::Exception &e ){
			CPPUNIT_FAIL("");
		}
		try{
			gd = gm->createGD( 800 , 600 , zefiro_graphics::ColorFormat::A8R8G8B8 , zefiro_graphics::DepthFormat::D16 , true  );
			gd->clear( zefiro_graphics::Color(0,255,0) , 0.0f );
			gd->present();
			Sleep(1000);
		}catch( zefiro_std::Exception &e ){
			CPPUNIT_FAIL("");
		}
	}

//CUPPA:decl=-

	CPPUNIT_TEST_SUITE(GraphicsDeviceTest);
    CPPUNIT_TEST(test_present);
	CPPUNIT_TEST_SUITE_END();

};
CPPUNIT_TEST_SUITE_REGISTRATION(GraphicsDeviceTest);
  