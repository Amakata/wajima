#include <graphics/sys/test/GraphicsModeTest.h>

CPPUNIT_TEST_SUITE_REGISTRATION( zefiro_graphicstest::GraphicsModeTest );

namespace zefiro_graphicstest{
	void GraphicsModeTest::setUp(){
		_mode = new zefiro_graphics::GraphicsMode( MODENUMBER , WIDTH , HEIGHT , REFRESHRATE , FORMAT );
	}
	void GraphicsModeTest::tearDown(){
		delete _mode;
	}
	void GraphicsModeTest::testGetModeNumber(){
		CPPUNIT_ASSERT_EQUAL( MODENUMBER , _mode->getModeNumber() );
	}
	void GraphicsModeTest::testGetWidth(){
		CPPUNIT_ASSERT_EQUAL( WIDTH , _mode->getWidth() );
	}
	void GraphicsModeTest::testGetHeight(){
		CPPUNIT_ASSERT_EQUAL( HEIGHT , _mode->getHeight() );
	}
	void GraphicsModeTest::testGetRefreshRate(){
		CPPUNIT_ASSERT_EQUAL( REFRESHRATE , _mode->getRefreshRate() );
	}
	void GraphicsModeTest::testGetFormat(){
		CPPUNIT_ASSERT_EQUAL( FORMAT , _mode->getFormat() );
	}
}