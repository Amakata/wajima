/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/main/include/test/Attic/GameTest.h,v 1.6 2002/04/28 14:52:15 ama Exp $
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
		CPPUNIT_TEST_SUITE_END();
	public:
		void setUp();
		void tearDown();
		void testGetPlayerSize();
		void testGetPhaseNumber();
		void testGetTurnNumber();
		void testIteratePhase();
	protected:
		zefiro_game::Game *_game;
	};
};

#endif //__GAMETEST_H__