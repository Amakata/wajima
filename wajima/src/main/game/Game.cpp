/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/main/game/Game.cpp,v 1.4 2002/04/28 13:36:16 ama Exp $
 */

#include "Game.h"

namespace zefiro_game {
	Game::Game():_playerSize(2){
	}
	int Game::getPlayerSize() const{
		return _playerSize;
	}
};

