/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/include/graphics/sys/Attic/Win32ImageSpriteImp.h,v 1.4 2002/04/29 16:28:02 ama Exp $
 */

#ifndef __WIN32IMAGESPRITEIMP_H__
#define __WIN32IMAGESPRITEIMP_H__

#include "graphics/ImageSpriteImp.h"
#include "graphics/sys/Win32SpriteFactory.h"

namespace zefiro_graphics {
	class Win32ImageSpriteImp : public ImageSpriteImp
	{
	private:
		/// コンストラクタ
		Win32ImageSpriteImp();
		friend zefiro_graphics::Win32SpriteFactory;
	public:
		/// コピーコンストラクタ
		/**
		 * \param win32ImageSpriteImp コピー元スプライトの実装クラス
		 */
		Win32ImageSpriteImp( const Win32ImageSpriteImp &win32ImageSpriteImp );
		/// デストラクタ
		virtual ~Win32ImageSpriteImp();
		/// 描画
		/**
		 *	\param xは横軸の描画位置である。
		 *	\param yは縦軸の描画位置である。
		 *	\param srcBaseSpriteImpは描画元BaseSpriteImpである。
		 */
		virtual void render( const int x , const int y , const BaseSpriteImp *srcBaseSpriteImp );
		/// スプライトの幅の取得
		/**
		 * \return  スプライトの幅
		 */
		virtual int getWidth() const;
		/// スプライトの高さの取得
		/**
		 * \return  スプライトの高さ
		 */
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
		 *	isTransparentableが透明か、半透明のどちらをサポートするかは
		 *	派生クラスの実装によって定まる。
		 */
		virtual void setTransparent( const bool transparent );
		///	透明・半透明処理の有無の取得
		/**
		 *	\retval true 透明・半透明処理を行う。
		 *	\retval false 透明・半透明処理を行わない。
		 */
		virtual bool isTransparent() const;
		virtual void setFrameNumber( const int number );
		virtual int getFrameNumber() const;
		virtual int getMaxFrameSize() const;
	};
};

#endif //__WIN32IMAGESPRITEIMP_H__