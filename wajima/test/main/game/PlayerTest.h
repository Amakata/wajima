/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/test/main/game/PlayerTest.h,v 1.1 2002/11/04 16:28:14 ama Exp $
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