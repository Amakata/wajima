#ifndef __GAMETEST_H__
#define __GAMETEST_H__

#include <cppunit/TestCaller.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/extensions/HelperMacros.h>

//#include "Game.h"

namespace zefiro_gametest{
	class GameTest : public CppUnit::TestCase {
		CPPUNIT_TEST_SUITE( GameTest );
//		CPPUNIT_TEST( test );
		CPPUNIT_TEST_SUITE_END();
	public:
		void setUp();
		void tearDown();
//		void test();
	protected:
	};
};

#endif //__GAMETEST_H__