/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/include/lib/std/test/Attic/AssertTest.h,v 1.1 2002/05/10 19:31:12 ama Exp $
 */

#ifndef __ASSERTTEST_H__
#define __ASSERTTEST_H__

#include <cppunit/TestCaller.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/extensions/HelperMacros.h>

namespace zefiro_stdtest {
	class AssertTest : public CppUnit::TestCase
	{
		CPPUNIT_TEST_SUITE( AssertTest );
		CPPUNIT_TEST( testAssertImplementation );
		CPPUNIT_TEST( testAssertNotEqualImplementation );
		CPPUNIT_TEST( testAssertEqualsTemplate );
		CPPUNIT_TEST( testAssertDoubleEqualsTemplate );
		CPPUNIT_TEST_SUITE_END();		
	public:
		void setUp();
		void tearDown();
		void testAssertImplementation();
		void testAssertNotEqualImplementation();
		void testAssertEqualsTemplate();
		void testAssertDoubleEqualsTemplate();
	};
};

#endif //__ASSERTTEST_H__