#ifndef __WIN32ASSERTTEST_H__
#define __WIN32ASSERTTEST_H__
/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/include/lib/std/sys/test/Attic/Win32AssertTest.h,v 1.2 2002/05/20 18:37:24 ama Exp $
 */
#include <cppunit/TestCaller.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/extensions/HelperMacros.h>

#include "std/sys/Win32Exception.h"

namespace zefiro_stdtest {
	class Win32AssertTest : public CppUnit::TestCase
	{
		CPPUNIT_TEST_SUITE( Win32AssertTest );
		CPPUNIT_TEST_EXCEPTION( testWin32Assert, zefiro_std::Win32Exception );
		CPPUNIT_TEST( testErrorSuccess );
		CPPUNIT_TEST_SUITE_END();
	public:
		void setUp();
		void tearDown();
		void testWin32Assert();
		void testErrorSuccess();
	protected:
	};
};

#endif //__WIN32ASSERTTEST_H__