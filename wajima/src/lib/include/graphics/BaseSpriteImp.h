/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/include/graphics/Attic/BaseSpriteImp.h,v 1.4 2002/04/29 16:27:34 ama Exp $
 */

#ifndef __BASESPRITEIMP_H__
#define __BASESPRITEIMP_H__

namespace zefiro_graphics{
	/**
	 * スプライトの実装クラスの仮想基底クラス
	 * 位置を指定したスプライトの実装クラス同士の描画や、
	 * スプライトの大きさ、色、透明、フレーム数の取り扱いが可能である。
	 */
	class BaseSpriteImp {
	public:
		/// コンストラクタ
		/**
		 *	仮想基底クラスであり、なにもしない。
		 */
		BaseSpriteImp();
		/// コピーコンストラクタ
		/**
		 *	仮想基底クラスであり、なにもしない。
		 */
		BaseSpriteImp( const BaseSpriteImp &baseSpriteImp );
		/// デストラクタ
		/**
		 *	仮想基底クラスであり、なにもしない。
		 * \param baseSpriteImp コピー元スプライトの実装クラス
		 */
		virtual ~BaseSpriteImp();
		/// 描画
		/**
		 *	\param xは横軸の描画位置である。
		 *	\param yは縦軸の描画位置である。
		 *	\param srcBaseSpriteImpは描画元BaseSpriteImpである。
		 */
		virtual void render( const int x , const int y , const BaseSpriteImp *srcBaseSpriteImp )=0;
		/// スプライトの幅の取得
		/**
		 * \return  スプライトの幅
		 */
		virtual int getWidth() const =0;
		/// スプライトの高さの取得
		/**
		 * \return  スプライトの高さ
		 */
		virtual int getHeight() const =0;
		/// 色数のビット深度
		/**
		 *	\return 色数のビット深度である。
		 *	例えば、65536色の場合、色数のビット深度は16である。
		 */
		virtual int getBitWidth() const =0;
		///	透明・半透明処理のサポート判定
		/**
		 *	\retval true 透明・半透明処理がサポートされている。
		 *	\retval	false 透明・半透明処理がサポートされていない。
		 */
		virtual bool isTransparentable() const =0;
		/// 透明・半透明処理の有無の設定
		/**
		 *	\param transparentは透明・半透明処理を行うか。
		 *	<ul>
		 *	<li>true 透明・半透明処理を行う。</li>
		 *	<li>false 透明・半透明処理を行わない。</li>
		 *	</ul>
		 *	isTransparentableが透明か、半透明のどちらをサポートするかは
		 *	派生クラスの実装によって定まる。
		 */
		virtual void setTransparent( const bool transparent ) =0;
		///	透明・半透明処理の有無の取得
		/**
		 *	\retval true 透明・半透明処理を行う。
		 *	\retval false 透明・半透明処理を行わない。
		 */
		virtual bool isTransparent() const =0;
		virtual void setFrameNumber( const int number ) =0;
		virtual int getFrameNumber() const =0;
		virtual int getMaxFrameSize() const =0;
	};
};
#endif //__BASESPRITEIMP_H__