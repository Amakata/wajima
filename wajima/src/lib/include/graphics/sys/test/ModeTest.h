/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/include/graphics/sys/test/Attic/ModeTest.h,v 1.2 2002/04/28 13:31:17 ama Exp $
 */

#ifndef __MODETEST_H__
#define __MODETEST_H__

#include <cppunit/TestCaller.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/extensions/HelperMacros.h>

#include <graphics/sys/Mode.h>

#define MODENUMBER	1
#define WIDTH		800
#define HEIGHT		600
#define REFRESHRATE	0
#define FORMAT	D3DFMT_R8G8B8

namespace zefiro_graphicstest{
	class ModeTest : public CppUnit::TestCase {
		CPPUNIT_TEST_SUITE( ModeTest );
		CPPUNIT_TEST( testGetModeNumber );
		CPPUNIT_TEST( testGetWidth );
		CPPUNIT_TEST( testGetHeight );
		CPPUNIT_TEST( testGetRefreshRate );
		CPPUNIT_TEST( testGetFormat );
		CPPUNIT_TEST( testToString );
		CPPUNIT_TEST_SUITE_END();
	public:
		void setUp();
		void tearDown();
		void testGetModeNumber();
		void testGetWidth();
		void testGetHeight();
		void testGetRefreshRate();
		void testGetFormat();
		void testToString();
	protected:
		zefiro_graphics::Mode *_mode;
	};
};

#endif //__MODETEST_H__