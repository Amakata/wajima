/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/main/game/test/Attic/GameTest.cpp,v 1.4 2002/04/28 13:24:31 ama Exp $
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
};