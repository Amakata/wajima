/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/main/include/test/Attic/PlayerTest.h,v 1.1 2002/04/28 17:33:10 ama Exp $
 */

#ifndef __PLAYERTEST_H__
#define __PLAYERTEST_H__

#include <cppunit/TestCaller.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Player.h"

namespace zefiro_gametest{
	class PlayerTest : public CppUnit::TestCase {
		CPPUNIT_TEST_SUITE( PlayerTest );
		CPPUNIT_TEST( testIsComputer );
		CPPUNIT_TEST_SUITE_END();
	public:
		void setUp();
		void tearDown();
		void testIsComputer();
	protected:
		zefiro_game::Player *_player;
	};
};


#endif //__PLAYERTEST_H__