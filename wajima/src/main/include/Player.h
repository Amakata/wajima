/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/main/include/Attic/Player.h,v 1.2 2002/05/08 15:16:37 ama Exp $
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