/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/std/sys/test/Attic/Win32AssertTest.cpp,v 1.3 2002/05/20 18:36:53 ama Exp $
 */

#include "std/sys/test/Win32AssertTest.h"

#include "std/sys/Win32Assert.h"

CPPUNIT_TEST_SUITE_REGISTRATION( zefiro_stdtest::Win32AssertTest );

namespace zefiro_stdtest {
	void Win32AssertTest::setUp(){
	}
	void Win32AssertTest::tearDown(){
	}
	void Win32AssertTest::testWin32Assert(){
		WIN32ASSERT( 1 );
	}
	void Win32AssertTest::testErrorSuccess(){
		WIN32ASSERT( ERROR_SUCCESS );
	}
};