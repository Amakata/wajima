/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/test/main/game/GameTest.h,v 1.1 2002/11/04 16:28:14 ama Exp $
 */

#ifndef __GAMETEST_H__
#define __GAMETEST_H__

#include <cppunit/TestCaller.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Game.h"

namespace zefiro_gametest{
	class GameTest : public CppUnit::TestCase {
		CPPUNIT_TEST_SUITE( GameTest );
		CPPUNIT_TEST( testGetPlayerSize );
		CPPUNIT_TEST( testGetPhaseNumber );
		CPPUNIT_TEST( testGetTurnNumber );
		CPPUNIT_TEST( testIteratePhase );
		CPPUNIT_TEST( testAddPlayer );
		CPPUNIT_TEST( testDeletePlayer );
		CPPUNIT_TEST_SUITE_END();
	public:
		void setUp();
		void tearDown();
		void testGetPlayerSize();
		void testGetPhaseNumber();
		void testGetTurnNumber();
		void testIteratePhase();
		void testAddPlayer();
		void testDeletePlayer();
	protected:
		zefiro_game::Game *_game;
		zefiro_game::Player *_player1;
		zefiro_game::Player *_player2;
	};
};

#endif //__GAMETEST_H__