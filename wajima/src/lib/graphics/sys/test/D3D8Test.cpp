#include <graphics/sys/test/D3D8Test.h>

CPPUNIT_TEST_SUITE_REGISTRATION( zefiro_graphicstest::D3D8Test );

namespace zefiro_graphicstest{
	void D3D8Test::setUp(){
		_d3d8 = new zefiro_graphics::D3D8();
	}
	void D3D8Test::tearDown(){
		delete _d3d8;
	}
	void D3D8Test::testModeCount(){
		CPPUNIT_ASSERT( 0 < _d3d8->getModeSize() );
	}
	void D3D8Test::testIsAvailable(){
		CPPUNIT_ASSERT_EQUAL( true , _d3d8->isAvailable() );
	}
};