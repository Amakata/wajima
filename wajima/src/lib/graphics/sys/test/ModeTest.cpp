/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/graphics/sys/test/Attic/ModeTest.cpp,v 1.2 2002/04/28 13:32:55 ama Exp $
 */

#include <sstream>

#include <graphics/sys/test/ModeTest.h>

CPPUNIT_TEST_SUITE_REGISTRATION( zefiro_graphicstest::ModeTest );

namespace zefiro_graphicstest{
	void ModeTest::setUp(){
		_mode = new zefiro_graphics::Mode( MODENUMBER , WIDTH , HEIGHT , REFRESHRATE , FORMAT );
	}
	void ModeTest::tearDown(){
		delete _mode;
	}
	void ModeTest::testGetModeNumber(){
		CPPUNIT_ASSERT_EQUAL( MODENUMBER , _mode->getModeNumber() );
	}
	void ModeTest::testGetWidth(){
		CPPUNIT_ASSERT_EQUAL( WIDTH , _mode->getWidth() );
	}
	void ModeTest::testGetHeight(){
		CPPUNIT_ASSERT_EQUAL( HEIGHT , _mode->getHeight() );
	}
	void ModeTest::testGetRefreshRate(){
		CPPUNIT_ASSERT_EQUAL( REFRESHRATE , _mode->getRefreshRate() );
	}
	void ModeTest::testGetFormat(){
		CPPUNIT_ASSERT_EQUAL( FORMAT , _mode->getFormat() );
	}
	void ModeTest::testToString(){
		std::ostringstream oss;
		oss << WIDTH << " " << HEIGHT << " " << REFRESHRATE << " " << FORMAT;
		CPPUNIT_ASSERT_EQUAL( oss.str() , _mode->toString() );
	}
}