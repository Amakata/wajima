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
	}
};