#ifndef __INVALIDARGUMENTTEST_H__
#define __INVALIDARGUMENTTEST_H__
/**
 * $Header: 
 */

#include <cppunit/TestCaller.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/extensions/HelperMacros.h>

#include <std/InvalidArgument.h>

namespace zefiro_stdtest {
	class InvalidArgumentTest : public CppUnit::TestCase
	{
		CPPUNIT_TEST_SUITE( InvalidArgumentTest );
		CPPUNIT_TEST( testConstruct );

		CPPUNIT_TEST_SUITE_END();		
	public:
		void setUp();
		void tearDown();
		void testConstruct();
	protected:
		zefiro_std::InvalidArgument *_notEqualException;
	};
};


#endif //__INVALIDARGUMENTTEST_H__