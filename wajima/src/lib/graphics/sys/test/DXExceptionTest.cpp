/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/graphics/sys/test/Attic/DXExceptionTest.cpp,v 1.1 2002/05/02 01:30:24 ama Exp $
 */

#include <std/InvalidArgument.h>

#include "graphics/sys/test/DXExceptionTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION( zefiro_graphicstest::DXExceptionTest );

#define HRESULT 1L
#define LINENUMBER 2L
#define FILENAME "test"

namespace zefiro_graphicstest{
	void DXExceptionTest::setUp(){
		_dxexception = new zefiro_graphics::DXException( HRESULT , LINENUMBER , FILENAME );
	}
	void DXExceptionTest::tearDown(){
		delete _dxexception;
	}
	void DXExceptionTest::testGetHResult(){
		CPPUNIT_ASSERT_EQUAL( HRESULT , _dxexception->getHResult() );
	}
	void DXExceptionTest::testLineNumber(){
		CPPUNIT_ASSERT_EQUAL( LINENUMBER , _dxexception->lineNumber() );
	}
	void DXExceptionTest::testFileName(){
		CPPUNIT_ASSERT_EQUAL( std::string(FILENAME), _dxexception->fileName() );
	}
	void DXExceptionTest::testIsInstanceOf(){
		CPPUNIT_ASSERT( _dxexception->isInstanceOf( zefiro_graphics::DXException::type() ) ); 
		CPPUNIT_ASSERT( _dxexception->isInstanceOf( zefiro_std::Exception::type() ) );
		CPPUNIT_ASSERT( !_dxexception->isInstanceOf( zefiro_std::InvalidArgument::type() ) );

	}
	void DXExceptionTest::testType(){
		CPPUNIT_ASSERT( zefiro_std::Exception::Type("zefiro_graphics::DXException") == zefiro_graphics::DXException::type() );
	}
};