#ifndef __EXCEPTIONTEST_H__
#define __EXCEPTIONTEST_H__

#include <cppunit/TestCaller.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/extensions/HelperMacros.h>

#include <string>

#include <std/Exception.h>

#define LINENUMBER 20L
#define MESSAGE std::string("test-message")
#define FILENAME std::string("test-file")

namespace zefiro_stdtest {
	class ExceptionTest : public CppUnit::TestCase
	{
		CPPUNIT_TEST_SUITE( ExceptionTest );
		CPPUNIT_TEST( testLineNumber );
		CPPUNIT_TEST( testFileName );
		CPPUNIT_TEST( testMessage );
		CPPUNIT_TEST( testClone );
		CPPUNIT_TEST( testCopy );
		CPPUNIT_TEST( testCopyConstruct );
		CPPUNIT_TEST( testType );
		CPPUNIT_TEST( testIsInstanceOf );
		CPPUNIT_TEST_SUITE_END();
	public:
		void setUp();
		void tearDown();
		void testLineNumber();
		void testFileName();
		void testMessage();
		void testClone();
		void testCopy();
		void testCopyConstruct();
		void testType();
		void testIsInstanceOf();
	protected:
		zefiro_std::Exception *_exception;
		zefiro_std::Exception *_exceptionDefault;
	};
};

#endif //__EXCEPTIONTEST_H__