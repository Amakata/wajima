/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/main/game/Player.h,v 1.1 2002/11/03 09:07:14 ama Exp $
 */

#ifndef __PLAYER_H__
#define __PLAYER_H__
namespace zefiro_game {
	/**
	 *	Player�̓v���[���̏��������A�s���̐U�镑�������肷��B
	 */
	class Player
	{
	public:
		/*
		 * �v���[�����R���s���[�^�����肷��B
		 *	\retval true ���̃v���[���̓R���s���[�^�ł���B
		 *	\retval false ���̃v���[��͐l�Ԃł���B
		 */
		bool isComputer() const;
	};
};
#endif //__PLAYER_H__