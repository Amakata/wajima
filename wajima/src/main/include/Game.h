/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/main/include/Attic/Game.h,v 1.4 2002/04/28 14:52:25 ama Exp $
 */

#ifndef __GAME_H__
#define __GAME_H__

namespace zefiro_game {
	/**
	 * Game�̓Q�[���S�̂�i�s���A�v���[���[�ɑ���̋@���z�����邱�Ƃ��ڂƂ���B
	 */
	class Game 
	{
	public:
		/**
		 *	�R���X�g���N�^
		 */
		Game();
		/**
		 * �Q�[��������v���[���[���̎擾���s���B
		 * �ʏ�A�l�ԂP�A�R���s���[�^�P�̍��v�Q�ƂȂ�B
		 * \return �v���[���[�̐�
		 */
		int getPlayerSize() const;
		/**
		 * ���݂̃t�F�[�Y���̎擾���s���B
		 * \return ���݂̃t�F�[�Y���B�ʏ�A0����getPlayerSize()-1�̒l��Ԃ��B
		 */
		int getCurrentPhaseNumber() const;
		/**
		 * ���݂̃^�[�����̎擾���s���B
		 * \return ���݂̃^�[����
		 */
		int getCurrentTurnNumber() const;
		/**
		 * �t�F�[�Y��1�i�߂�B�^�[���������I�ɍX�V�����B
		 */
		void iteratePhase();
	private:
		int _playerSize;			///<	�v���[���l��
		int _currentPhaseNumber;	///<	���݂̃t�F�[�Y�ԍ�
		int _currentTurnNumber;		///<	���݂̃^�[���ԍ�
	};
};

#endif //__GAME_H__