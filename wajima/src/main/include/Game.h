/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/main/include/Attic/Game.h,v 1.5 2002/04/28 17:34:10 ama Exp $
 */

#ifndef __GAME_H__
#define __GAME_H__

#include <vector>

#include "Player.h"

namespace zefiro_game {
	/**
	 * Gameはゲーム全体を進行し、プレーヤーに操作の機会を配分することを役目とする。
	 */
	class Game 
	{
	public:
		/**
		 *	コンストラクタ
		 */
		Game();
		/**
		 * ゲームをするプレーヤー数の取得を行う。
		 * 通常、人間１、コンピュータ１の合計２となる。
		 * \return プレーヤーの数
		 */
		int getPlayerSize() const;
		/**
		 * 現在のフェーズ数の取得を行う。
		 * \return 現在のフェーズ数。通常、0からgetPlayerSize()-1の値を返す。
		 */
		int getCurrentPhaseNumber() const;
		/**
		 * 現在のターン数の取得を行う。
		 * \return 現在のターン数
		 */
		int getCurrentTurnNumber() const;
		/**
		 * フェーズを1進める。ターンも自動的に更新される。
		 */
		void iteratePhase();
		/**
		 * ゲームに参加するプレーヤを追加する。
		 * \param player 追加するプレーヤ
		 */
		void addPlayer( Player *player );
		/**
		 * ゲームに参加しているプレーヤを削除する。
		 * ただし、削除するのはポインタのみで、実体は削除しない。
		 * \param player 削除するプレーヤ
		 */
		void deletePlayer( Player *player );
	private:
		std::vector<Player*>	_players;	///< プレーヤーの配列
		int _currentPhaseNumber;	///<	現在のフェーズ番号
		int _currentTurnNumber;		///<	現在のターン番号
	};
};

#endif //__GAME_H__