/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/graphics/sys/test/Attic/D3D8Test.cpp,v 1.7 2002/04/29 16:25:57 ama Exp $
 */

#include "graphics/sys/test/D3D8Test.h"

CPPUNIT_TEST_SUITE_REGISTRATION( zefiro_graphicstest::D3D8Test );

namespace zefiro_graphicstest{
	void D3D8Test::setUp(){
		_d3d8 = new zefiro_graphics::D3D8();
	}
	void D3D8Test::tearDown(){
		delete _d3d8;
	}
	void D3D8Test::testAdapterCount(){
		CPPUNIT_ASSERT( 0 < _d3d8->getAdapterCount() );
	}
	void D3D8Test::testAdapterModeCount(){
		for( int i=0 ; i<_d3d8->getAdapterCount() ; ++i ){
			CPPUNIT_ASSERT( 0 < _d3d8->getAdapterModeCount( i ) );
		}
	}
	void D3D8Test::testGetAdapterVector(){
		std::vector<zefiro_graphics::Adapter> adapters = _d3d8->getAdapterVector();
		CPPUNIT_ASSERT( 0 < adapters.size() );
	}
	void D3D8Test::testIsAvailable(){
		CPPUNIT_ASSERT_EQUAL( true , _d3d8->isAvailable() );
	}
};