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
		CPPUNIT_TEST( testLineNumber );
		CPPUNIT_TEST( testFileName );
		CPPUNIT_TEST( testWhat );
		CPPUNIT_TEST( testInstanceOf );
		CPPUNIT_TEST_SUITE_END();		
	public:
		void setUp();
		void tearDown();
		void testLineNumber();
		void testFileName();
		void testWhat();
		void testInstanceOf();
	protected:
		zefiro_std::InvalidArgument *_invalidArgument;
	};
};


#endif //__INVALIDARGUMENTTEST_H__