/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/include/graphics/sys/test/Attic/AdapterTest.h,v 1.2 2002/04/28 13:31:17 ama Exp $
 */

#ifndef __ADAPTERTEST_H__
#define __ADAPTERTEST_H__

#include <cppunit/TestCaller.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/extensions/HelperMacros.h>

#define ADAPTERNAME		"adaptername"
#define ADAPTERNUMBER	1

#include <graphics/sys/Adapter.h>
#include <graphics/sys/Mode.h>

namespace zefiro_graphicstest{
	class AdapterTest : public CppUnit::TestCase {
		CPPUNIT_TEST_SUITE( AdapterTest );
		CPPUNIT_TEST( testGetName );
		CPPUNIT_TEST( testGetAdapterNumber );
		CPPUNIT_TEST( testGetModeVector );
		CPPUNIT_TEST( testToString );
		CPPUNIT_TEST_SUITE_END();
	public:
		void setUp();
		void tearDown();
		void testGetName();
		void testGetAdapterNumber();
		void testGetModeVector();
		void testToString();
	protected:
		zefiro_graphics::Adapter *_adapter;
	};
};

#endif //__ADAPTERTEST_H__