/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/include/main/Attic/Player.h,v 1.1 2002/05/10 19:31:40 ama Exp $
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