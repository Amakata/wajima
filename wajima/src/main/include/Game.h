/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/main/include/Attic/Game.h,v 1.3 2002/04/28 13:36:11 ama Exp $
 */

#ifndef __GAME_H__
#define __GAME_H__

namespace zefiro_game {
	class Game 
	{
	public:
		Game();
		int getPlayerSize() const;
	private:
		int _playerSize;
	};
};

#endif //__GAME_H__