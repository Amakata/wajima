/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/include/main/Attic/Player.h,v 1.1 2002/05/10 19:31:40 ama Exp $
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