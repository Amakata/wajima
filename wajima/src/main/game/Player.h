/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/main/game/Player.h,v 1.1 2002/11/03 09:07:14 ama Exp $
 */

#ifndef __PLAYER_H__
#define __PLAYER_H__
namespace zefiro_game {
	/**
	 *	Playerはプレーヤの情報を持ち、行動の振る舞いを決定する。
	 */
	class Player
	{
	public:
		/*
		 * プレーヤがコンピュータか判定する。
		 *	\retval true このプレーヤはコンピュータである。
		 *	\retval false このプレーやは人間である。
		 */
		bool isComputer() const;
	};
};
#endif //__PLAYER_H__