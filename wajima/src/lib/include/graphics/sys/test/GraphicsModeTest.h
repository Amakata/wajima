#ifndef __GRAPHICSMODETEST_H__
#define __GRAPHICSMODETEST_H__

#include <cppunit/TestCaller.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/extensions/HelperMacros.h>

#include <graphics/sys/GraphicsMode.h>

#define MODENUMBER	1
#define WIDTH		800
#define HEIGHT		600
#define REFRESHRATE	0
#define FORMAT	D3DFMT_R8G8B8

namespace zefiro_graphicstest{
	class GraphicsModeTest : public CppUnit::TestCase {
		CPPUNIT_TEST_SUITE( GraphicsModeTest );
		CPPUNIT_TEST( testGetModeNumber );
		CPPUNIT_TEST( testGetWidth );
		CPPUNIT_TEST( testGetHeight );
		CPPUNIT_TEST( testGetRefreshRate );
		CPPUNIT_TEST( testGetFormat );
		CPPUNIT_TEST_SUITE_END();
	public:
		void setUp();
		void tearDown();
		void testGetModeNumber();
		void testGetWidth();
		void testGetHeight();
		void testGetRefreshRate();
		void testGetFormat();
	protected:
		zefiro_graphics::GraphicsMode *_mode;
	};
};

#endif //__GRAPHICSMODETEST_H__