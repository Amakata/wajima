#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
//CUPPA:include=+
#include "SmartPtr.h"
#include "std/Exception.h"
#include "std/InvalidArgument.h"
#include "graphics/GraphicsManager.h"
#include "graphics/GraphicsDevice.h"
#include "Config.h"
//CUPPA:include=-

class GraphicsManagerTest : public CppUnit::TestFixture {
//CUPPA:usercode=+

private:
	typedef zefiro_graphics::GraphicsDevice::GD GD;
	typedef zefiro_graphics::GraphicsManager::GM GM;
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
    void test_createGM() {
		try{
			GM gm = zefiro_graphics::GraphicsManager::createGM( 0 );
			CPPUNIT_FAIL("");
		}catch( zefiro_std::InvalidArgument &e ){
		}
		try{
			GM gm = zefiro_graphics::GraphicsManager::createGM( Config::getHWND() );
		}catch( zefiro_std::Exception &e ){
			CPPUNIT_FAIL("");
		}
	}
    void test_createGD() {
		GM gm;
		GD gd;
		try{
			gm = zefiro_graphics::GraphicsManager::createGM( Config::getHWND() );
		}catch( zefiro_std::Exception &e ){
			CPPUNIT_FAIL("");
		}
		try{
			gd = gm->createGD( 800 , 600 , zefiro_graphics::ColorFormat::A8R8G8B8 , zefiro_graphics::DepthFormat::D16 , false  );
		}catch( zefiro_std::InvalidArgument &e ){
			CPPUNIT_FAIL("");
		}

	}
//CUPPA:decl=-

	CPPUNIT_TEST_SUITE(GraphicsManagerTest);
    CPPUNIT_TEST(test_createGM);
    CPPUNIT_TEST(test_createGD);
	CPPUNIT_TEST_SUITE_END();

};
CPPUNIT_TEST_SUITE_REGISTRATION(GraphicsManagerTest);
  