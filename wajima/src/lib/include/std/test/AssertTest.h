#ifndef __ASSERTTEST_H__
#define __ASSERTTEST_H__

#include <cppunit/TestCaller.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/Failure.h>

namespace zefiro_stdtest {
	class AssertTest : public CppUnit::TestCase
	{
		CPPUNIT_TEST_SUITE( AssertTest );
		CPPUNIT_TEST( testAssertImplementation );
		CPPUNIT_TEST( testAssertNotEqualImplementation );
		CPPUNIT_TEST_SUITE_END();		
	public:
		void setUp();
		void tearDown();
		void testAssertImplementation();
		void testAssertNotEqualImplementation();
	};
};

#endif //__ASSERTTEST_H__