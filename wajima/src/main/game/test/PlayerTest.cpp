/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/main/game/test/Attic/PlayerTest.cpp,v 1.1 2002/04/28 17:33:16 ama Exp $
 */

#include "test/PlayerTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION( zefiro_gametest::PlayerTest );

namespace zefiro_gametest {
	void PlayerTest::setUp(){
		_player = new zefiro_game::Player();
	}
	void PlayerTest::tearDown(){
		delete _player;
	}
	void PlayerTest::testIsComputer(){
		CPPUNIT_ASSERT( !_player->isComputer() );
	}
};