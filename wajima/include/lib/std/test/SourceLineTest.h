#ifndef __SOURCELINETEST_H__
#define __SOURCELINETEST_H__
/**
 * $Header: 
 */

#include <cppunit/TestCaller.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/extensions/HelperMacros.h>

#include "std/SourceLine.h"

namespace zefiro_stdtest {
	class SourceLineTest : public CppUnit::TestCase
	{
		CPPUNIT_TEST_SUITE( SourceLineTest );
		CPPUNIT_TEST( testLineNumber );
		CPPUNIT_TEST( testFileName );
		CPPUNIT_TEST( testIsValid );
		CPPUNIT_TEST( testEqual );
		CPPUNIT_TEST( testNotEqual );
		CPPUNIT_TEST( testUseCase1 );
		CPPUNIT_TEST( testUseCase2 );
		CPPUNIT_TEST_SUITE_END();
	protected:
		zefiro_std::SourceLine *_sourceLine;
		zefiro_std::SourceLine *_sourceLineDefault;
	public:
		void setUp();
		void tearDown();
		void testLineNumber();
		void testFileName();
		void testIsValid();
		void testEqual();
		void testNotEqual();
		void testUseCase1();
		void testUseCase2();
	};
};

#endif //__SOURCELINETEST_H__