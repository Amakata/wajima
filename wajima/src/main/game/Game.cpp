/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/main/game/Game.cpp,v 1.7 2002/04/28 17:43:00 ama Exp $
 */

#include <std/Assert.h>

#include "Game.h"

namespace zefiro_game {
	Game::Game():_currentPhaseNumber(0),_currentTurnNumber(0){
	}
	int Game::getPlayerSize() const{
		return _players.size();
	}
	int Game::getCurrentPhaseNumber() const{
		return _currentPhaseNumber;
	}
	int Game::getCurrentTurnNumber() const{
		return _currentTurnNumber;
	}
	void Game::iteratePhase() {
		ZEFIRO_STD_ASSERT( 0 != getPlayerSize() );
		++_currentPhaseNumber;
		if( _currentPhaseNumber  == getPlayerSize() ){
			++_currentTurnNumber;
			_currentPhaseNumber = 0;
		}
	}
	void Game::addPlayer( Player *player ){
		_players.push_back( player );
	}
	void Game::deletePlayer( Player *player ){
		for( std::vector<Player*>::iterator players = _players.begin() ; players < _players.end() ; ++players ){
			if( *players == player ){
				_players.erase( players );
				return;
			}
		}
	}
};

