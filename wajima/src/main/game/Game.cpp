/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/main/game/Game.cpp,v 1.5 2002/04/28 14:52:29 ama Exp $
 */

#include "Game.h"

namespace zefiro_game {
	Game::Game():_playerSize(2),_currentPhaseNumber(0),_currentTurnNumber(0){
	}
	int Game::getPlayerSize() const{
		return _playerSize;
	}
	int Game::getCurrentPhaseNumber() const{
		return _currentPhaseNumber;
	}
	int Game::getCurrentTurnNumber() const{
		return _currentTurnNumber;
	}
	void Game::iteratePhase() {
		++_currentPhaseNumber;
		if( _currentPhaseNumber  == getPlayerSize() ){
			++_currentTurnNumber;
			_currentPhaseNumber = 0;
		}
	}
};

