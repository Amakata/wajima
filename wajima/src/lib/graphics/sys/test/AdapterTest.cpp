/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/graphics/sys/test/Attic/AdapterTest.cpp,v 1.3 2002/04/29 16:25:57 ama Exp $
 */

#include <sstream>

#include "graphics/sys/test/AdapterTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION( zefiro_graphicstest::AdapterTest );

namespace zefiro_graphicstest{
	void AdapterTest::setUp(){
		_adapter = new zefiro_graphics::Adapter( ADAPTERNUMBER , ADAPTERNAME);
	}
	void AdapterTest::tearDown(){
		delete _adapter;
	}
	void AdapterTest::testGetName(){
		CPPUNIT_ASSERT_EQUAL( _adapter->getName() , std::string(ADAPTERNAME) );
	}
	void AdapterTest::testGetAdapterNumber(){
		CPPUNIT_ASSERT_EQUAL( _adapter->getAdapterNumber() , ADAPTERNUMBER );
	}
	void AdapterTest::testGetModeVector(){
		_adapter->addMode( zefiro_graphics::Mode( 1 , 800 , 600 , 0 , D3DFMT_R8G8B8 ) );
		std::vector<zefiro_graphics::Mode> modes = _adapter->getModeVector();
		CPPUNIT_ASSERT_EQUAL( (UINT)1 , modes.size() );
		CPPUNIT_ASSERT_EQUAL( zefiro_graphics::Mode( 1 , 800 , 600 , 0 , D3DFMT_R8G8B8 ).toString() , modes[0].toString() );
	}
	void AdapterTest::testToString(){
		_adapter->addMode( zefiro_graphics::Mode( 1 , 800 , 600 , 0 , D3DFMT_R8G8B8 ) );
		std::ostringstream oss;
		oss << std::string(ADAPTERNAME) 
			<< std::endl 
			<< zefiro_graphics::Mode( 1 , 800 , 600 , 0 , D3DFMT_R8G8B8 ).toString()
			<< std::endl;

		CPPUNIT_ASSERT_EQUAL( oss.str() , _adapter->toString() );
	}
};