/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/include/lib/graphics/sys/test/Attic/D3D8Test.h,v 1.2 2002/05/23 15:59:22 ama Exp $
 */

#ifndef __D3D8TEST_H__
#define __D3D8TEST_H__

#include <cppunit/TestCaller.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/extensions/HelperMacros.h>

#include "graphics/sys/D3D8.h"

namespace zefiro_graphicstest{
	class D3D8Test : public CppUnit::TestCase {
		CPPUNIT_TEST_SUITE( D3D8Test );
		CPPUNIT_TEST( testAdapterCount );
		CPPUNIT_TEST( testAdapterModeCount );
		CPPUNIT_TEST( testIsAvailable );
		CPPUNIT_TEST( testGetAdapterVector );
		CPPUNIT_TEST_SUITE_END();
	public:
		void setUp();
		void tearDown();
		void testAdapterCount();
		void testAdapterModeCount();
		void testGetAdapterVector();
		void testIsAvailable();
	protected:
		zefiro_graphics::D3D8 *_d3d8;
	};
};

#endif //__D3D8TEST_H__