/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/include/lib/graphics/sys/test/Attic/DXExceptionTest.h,v 1.2 2002/05/23 15:59:22 ama Exp $
 */
#ifndef __DXEXCEPTIONTEST_H__
#define __DXEXCEPTIONTEST_H__

#include <cppunit/TestCaller.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/extensions/HelperMacros.h>

#include "graphics/sys/DXException.h"

namespace zefiro_graphicstest {

	class DXExceptionTest : public CppUnit::TestCase {
		CPPUNIT_TEST_SUITE( DXExceptionTest );
		CPPUNIT_TEST( testGetHResult );
		CPPUNIT_TEST( testLineNumber );
		CPPUNIT_TEST( testFileName );
		CPPUNIT_TEST( testIsInstanceOf );
		CPPUNIT_TEST( testType );
		CPPUNIT_TEST_SUITE_END();
	public:
		void setUp();
		void tearDown();
		void testGetHResult();
		void testLineNumber();
		void testFileName();
		void testIsInstanceOf();
		void testType();
	protected:
		zefiro_graphics::DXException *_dxexception;
	};
};


#endif //__DXEXCEPTIONTEST_H__