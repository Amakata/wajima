/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/include/std/test/Attic/NotEqualExceptionTest.h,v 1.2 2002/04/28 13:31:34 ama Exp $
 */

#ifndef __NOTEQUALEXCEPTIONTEST_H__
#define __NOTEQUALEXCEPTIONTEST_H__


#include <cppunit/TestCaller.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/extensions/HelperMacros.h>

#include <std/NotEqualException.h>

namespace zefiro_stdtest {
	class NotEqualExceptionTest : public CppUnit::TestCase
	{
		CPPUNIT_TEST_SUITE( NotEqualExceptionTest );
		CPPUNIT_TEST( testConstruct );
		CPPUNIT_TEST( testCopyConstruct );
		CPPUNIT_TEST( testCopy );
		CPPUNIT_TEST( testClone );
		CPPUNIT_TEST( testFileName );
		CPPUNIT_TEST( testLineNumber );
		CPPUNIT_TEST( testExpectedValue );
		CPPUNIT_TEST( testActualValue );
		CPPUNIT_TEST( testType );
		CPPUNIT_TEST( testIsInstanceOf );
		CPPUNIT_TEST_SUITE_END();		
	public:
		void setUp();
		void tearDown();
		void testConstruct();
		void testCopyConstruct();
		void testCopy();
		void testClone();
		void testFileName();
		void testLineNumber();
		void testExpectedValue();
		void testActualValue();
		void testType();
		void testIsInstanceOf();
	protected:
		zefiro_std::NotEqualException *_notEqualException;
	};
};

#endif //__NOTEQUALEXCEPTIONTEST_H__