/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/test/main/game/GameTest.cpp,v 1.1 2002/11/04 16:28:14 ama Exp $
 */

#include "test/GameTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION( zefiro_gametest::GameTest );

namespace zefiro_gametest{
	void GameTest::setUp(){
		_game = new zefiro_game::Game();
		_player1 = new zefiro_game::Player();
		_player2 = new zefiro_game::Player();
	}
	void GameTest::tearDown(){
		delete _player2;
		delete _player1;
		delete _game;
	}
	void GameTest::testGetPlayerSize(){
		CPPUNIT_ASSERT_EQUAL( 0 , _game->getPlayerSize() );
	}
	void GameTest::testGetPhaseNumber(){
		CPPUNIT_ASSERT_EQUAL( 0 , _game->getCurrentPhaseNumber() );
	}
	void GameTest::testGetTurnNumber(){
		CPPUNIT_ASSERT_EQUAL( 0 , _game->getCurrentTurnNumber() );
	}
	void GameTest::testIteratePhase(){
		_game->addPlayer( _player1 );
		_game->addPlayer( _player2 );
		for( int turn = 0 ; turn < 10 ; ++turn ){
			CPPUNIT_ASSERT_EQUAL( turn , _game->getCurrentTurnNumber() );
			for( int phase = 0 ; phase < _game->getPlayerSize() ; ++phase ){
				CPPUNIT_ASSERT_EQUAL( phase , _game->getCurrentPhaseNumber() );
				_game->iteratePhase();
			}
		}

	}
	void GameTest::testAddPlayer(){
		CPPUNIT_ASSERT_EQUAL( 0 , _game->getPlayerSize() );
		_game->addPlayer( _player1 );
		CPPUNIT_ASSERT_EQUAL( 1 , _game->getPlayerSize() );
		_game->addPlayer( _player2 );
		CPPUNIT_ASSERT_EQUAL( 2 , _game->getPlayerSize() );
	}
	void GameTest::testDeletePlayer(){
		_game->addPlayer( _player1 );
		_game->addPlayer( _player2 );
		CPPUNIT_ASSERT_EQUAL( 2 , _game->getPlayerSize() );
		_game->deletePlayer( _player1 );
		CPPUNIT_ASSERT_EQUAL( 1 , _game->getPlayerSize() );
		_game->deletePlayer( _player2 );
		CPPUNIT_ASSERT_EQUAL( 0 , _game->getPlayerSize() );

		// 同じプレーヤーを２回追加した場合も、削除は一つづつするべき。
		_game->addPlayer( _player1 );
		_game->addPlayer( _player2 );
		_game->addPlayer( _player1 );
		CPPUNIT_ASSERT_EQUAL( 3 , _game->getPlayerSize() );
		_game->deletePlayer( _player1 );
		CPPUNIT_ASSERT_EQUAL( 2 , _game->getPlayerSize() );
		_game->deletePlayer( _player1 );
		CPPUNIT_ASSERT_EQUAL( 1 , _game->getPlayerSize() );
		_game->deletePlayer( _player2 );
		CPPUNIT_ASSERT_EQUAL( 0 , _game->getPlayerSize() );

	}
};