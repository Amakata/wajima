/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/main/include/Attic/Player.h,v 1.1 2002/04/28 17:33:27 ama Exp $
 */

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