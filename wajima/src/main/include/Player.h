/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/main/include/Attic/Player.h,v 1.1 2002/04/28 17:33:27 ama Exp $
 */

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