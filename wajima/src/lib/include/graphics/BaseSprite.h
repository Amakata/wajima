/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/include/graphics/Attic/BaseSprite.h,v 1.3 2002/04/28 13:31:05 ama Exp $
 */

#ifndef __BASESPRITE_H__
#define __BASESPRITE_H__

#include <graphics/BaseSpriteImp.h>

namespace zefiro_graphics{
	/**
	 *	ベーススプライト
	 *	描画位置を持たない軽量スプライトである。
	 */
	class BaseSprite
	{
	public:
		/// コンストラクタ
		/**
		 *	\param baseSpriteImpはBaseSpriteが取り扱うスプライトの実装クラスへのポインタである。
		 *	BaseSpriteクラスはbaseSpriteImpのdeleteを行わない。baseSpriteImpのdeleteはユーザの責任である。
		 */
		BaseSprite( BaseSpriteImp *baseSpriteImp );
		///	コピーコンストラクタ
		/**
		 *	\param baseSpriteはコピー元のBaseSpriteクラス
		 *	BaseSpriteの深いコピーを行う。
		 */
		BaseSprite( const BaseSprite &baseSprite );
		/// デストラクタ
		virtual ~BaseSprite();
		/// 描画
		/**
		 *	\param xは横軸の描画位置である。
		 *	\param yは縦軸の描画位置である。
		 *	\param srcBaseSpriteは描画元BaseSpriteである。
		 */
		virtual void render( const int x , const int y , const BaseSprite &srcBaseSprite ); 
		virtual int getWidth() const;
		virtual int getHeight() const;
		/// 色数のビット深度
		/**
		 *	\return 色数のビット深度である。
		 *	例えば、65536色の場合、色数のビット深度は16である。
		 */
		virtual int getBitWidth() const;
		///	透明・半透明処理のサポート判定
		/**
		 *	\retval true 透明・半透明処理がサポートされている。
		 *	\retval	false 透明・半透明処理がサポートされていない。
		 */
		virtual bool isTransparentable() const;
		/// 透明・半透明処理の有無の設定
		/**
		 *	\param transparentは透明・半透明処理を行うか。
		 *	<ul>
		 *	<li>true 透明・半透明処理を行う。</li>
		 *	<li>false 透明・半透明処理を行わない。</li>
		 *	</ul>
		 */
		virtual void setTransparent( const bool transparent );
		///	透明・半透明処理の有無の取得
		/**
		 *	\retval true 透明・半透明処理を行う。
		 *	\retval false 透明・半透明処理を行わない。
		 */
		virtual bool isTransparent() const;
		/// 描画処理の有無の設定
		/**
		 *	\param renderは描画処理を行うか。
		 */
		virtual void setRender( const bool render );
		/// 描画処理の有無の取得
		/**
		 *	\retval true 描画処理を行う。
		 *	\retval false 描画処理を行わない。
		 */
		virtual bool isRender() const;
		/// 描画フレームの設定
		/**
		 *	\param numberは描画するフレームの番号である。
		 */
		virtual void setFrameNumber( const int number );
		///	描画フレームの取得
		/**
		 *	\return 描画するフレームの番号である。
		 */
		virtual int getFrameNumber() const;
		///	描画フレームの最大サイズの取得
		/**
		 *	\return 描画フレームの最大サイズである。getMaxFrameSize()-1までsetFrameNumberで設定できる。
		 */
		virtual int getMaxFrameSize() const;
	protected:
		BaseSpriteImp *_baseSpriteImp;	///< スプライトの実装クラス
		bool _render;					///< スプライト描画処理の有無
	};
};

#endif //__BASESPRITE_H__