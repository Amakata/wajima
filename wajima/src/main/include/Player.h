/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/main/include/Attic/Player.h,v 1.2 2002/05/08 15:16:37 ama Exp $
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