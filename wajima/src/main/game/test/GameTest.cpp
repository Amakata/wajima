/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/main/game/test/Attic/GameTest.cpp,v 1.5 2002/04/28 14:52:11 ama Exp $
 */

#include "test/GameTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION( zefiro_gametest::GameTest );

namespace zefiro_gametest{
	void GameTest::setUp(){
		_game = new zefiro_game::Game();
	}
	void GameTest::tearDown(){
		delete _game;
	}
	void GameTest::testGetPlayerSize(){
		CPPUNIT_ASSERT_EQUAL( 2 , _game->getPlayerSize() );
	}
	void GameTest::testGetPhaseNumber(){
		CPPUNIT_ASSERT_EQUAL( 0 , _game->getCurrentPhaseNumber() );
	}
	void GameTest::testGetTurnNumber(){
		CPPUNIT_ASSERT_EQUAL( 0 , _game->getCurrentTurnNumber() );
	}
	void GameTest::testIteratePhase(){
		for( int turn = 0 ; turn < 10 ; ++turn ){
			CPPUNIT_ASSERT_EQUAL( turn , _game->getCurrentTurnNumber() );
			for( int phase = 0 ; phase < _game->getPlayerSize() ; ++phase ){
				CPPUNIT_ASSERT_EQUAL( phase , _game->getCurrentPhaseNumber() );
				_game->iteratePhase();
			}
		}
	}
};