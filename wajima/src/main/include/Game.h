/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/main/include/Attic/Game.h,v 1.4 2002/04/28 14:52:25 ama Exp $
 */

#ifndef __GAME_H__
#define __GAME_H__

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
	private:
		int _playerSize;			///<	プレーヤ人数
		int _currentPhaseNumber;	///<	現在のフェーズ番号
		int _currentTurnNumber;		///<	現在のターン番号
	};
};

#endif //__GAME_H__