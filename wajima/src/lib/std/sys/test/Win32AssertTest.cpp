/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/std/sys/test/Attic/Win32AssertTest.cpp,v 1.2 2002/05/10 19:49:53 ama Exp $
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
		WIN32ASSERT( GetLastError() );
	}
};