/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/include/std/Attic/UniqueNumberFactory.h,v 1.4 2002/04/29 16:28:42 ama Exp $
 */

#ifndef __UNIQUENUMBERFACTORY_H__
#define __UNIQUENUMBERFACTORY_H__

#include <vector>

#include "std/UniqueNumberBadAlloc.h"

namespace zefiro_std{
	/**	ユニークナンバー生成クラス。
	 *	一度、生成されたナンバーは削除しない限り生成されない。
	 *	削除されたナンバーは記憶され、再利用される。
	 */
	class UniqueNumberFactory
	{
	public:
		/** コンストラクタ
		 * \param begin_number ユニークナンバーの開始番号
		 */
		UniqueNumberFactory( int begin_number = 0 );
		///	デストラクタ
		virtual ~UniqueNumberFactory();
		/**
		 * ユニークナンバーの生成
		 *	\return 生成されたユニークナンバー
		 * \throw zefiro_std::unique_number_bad_alloc ユニークナンバーの生成範囲を超える生成を行った。
		 */
		virtual int createNumber() throw(zefiro_std::UniqueNumberBadAlloc);			
		/**
		 *	ユニークナンバーの削除
		 *	\param number 削除するユニークナンバー
		 */
		virtual void deleteNumber( int number );
	protected:
		/**
		 * 削除したユニークナンバーの集合にnumberは含まれるか判定する。
		 * \param number 削除したユニークナンバーの集合に含まれるか判定するナンバー
		 * \retval true 削除したユニークナンバーの集合に含まれる。
		 * \retval false 削除したユニークナンバーの集合に含まれない。
		 * \throw std::invalid_argument 利用していないユニークナンバーを指定した。
		*/
		virtual bool isContainedInDeletedUniqueNumbers( int number ) throw(std::invalid_argument);
		/**
		 * 利用されているユニークナンバーに含まれるか判定する。
		 * \param number 利用しているか判定するユニークナンバー
		 * \retval true numberのユニークナンバーは利用されている。
		 * \retval false numberのユニークナンバーは利用されていない。
		 */
		virtual bool isContainedInUsedUniqueNumbers( int number );
		std::vector<int>	_deletedUniqueNumbers;		///<	削除したユニークナンバーの集合
		int					_maxUniqueNumber;			///<	最大のユニークナンバー
	};
};
#endif //__UNIQUENUMBERFACTORY_H__