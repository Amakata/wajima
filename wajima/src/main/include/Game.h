/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/main/include/Attic/Game.h,v 1.5 2002/04/28 17:34:10 ama Exp $
 */

#ifndef __GAME_H__
#define __GAME_H__

#include <vector>

#include "Player.h"

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
		/**
		 * �Q�[���ɎQ������v���[����ǉ�����B
		 * \param player �ǉ�����v���[��
		 */
		void addPlayer( Player *player );
		/**
		 * �Q�[���ɎQ�����Ă���v���[�����폜����B
		 * �������A�폜����̂̓|�C���^�݂̂ŁA���͍̂폜���Ȃ��B
		 * \param player �폜����v���[��
		 */
		void deletePlayer( Player *player );
	private:
		std::vector<Player*>	_players;	///< �v���[���[�̔z��
		int _currentPhaseNumber;	///<	���݂̃t�F�[�Y�ԍ�
		int _currentTurnNumber;		///<	���݂̃^�[���ԍ�
	};
};

#endif //__GAME_H__