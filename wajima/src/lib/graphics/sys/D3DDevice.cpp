/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/graphics/sys/Attic/D3DDevice.cpp,v 1.8 2002/09/20 02:33:30 ama Exp $
 */

#include "graphics/sys/D3DDevice.h"
#include "graphics/sys/DXAssert.h"
#include <d3dx8tex.h>
#include "std/Logger.h"
#include <sstream>

#define D3DFVF_CUSTOMVERTEX	(D3DFVF_XYZRHW|D3DFVF_TEX1)

typedef struct CUSTOMVERTEX_ {
	float x,y,z,rhw;
	float tu,tv;
}CUSTOMVERTEX;

namespace zefiro_graphics {
	D3DDevice::D3DDevice( LPDIRECT3DDEVICE8 d3ddevice8 ):d3dDevice8_(d3ddevice8){
		DXASSERT( d3dDevice8_->SetRenderState( D3DRS_ZENABLE  , D3DZB_TRUE ) );
		DXASSERT( d3dDevice8_->SetRenderState( D3DRS_ZWRITEENABLE , TRUE ) );
//		d3dDevice8_->SetRenderState( D3DRS_ALPHAREF , 0 );
//		d3dDevice8_->SetRenderState( D3DRS_ALPHATESTENABLE , TRUE );
//		d3dDevice8_->SetRenderState( D3DRS_ALPHAFUNC , D3DCMP_GREATEREQUAL );
//		d3dDevice8_->SetRenderState( D3DRS_ALPHABLENDENABLE , TRUE );
//		d3dDevice8_->SetRenderState( D3DRS_SRCBLEND , D3DBLEND_SRCALPHA );
//		d3dDevice8_->SetRenderState( D3DRS_DESTBLEND , D3DBLEND_INVSRCALPHA );
//		d3dDevice8_->SetRenderState( D3DRS_BLENDOP , D3DBLENDOP_ADD );	
//		DXASSERT( d3dDevice8_->SetRenderState( D3DRS_CULLMODE , FALSE ) );
		DXASSERT( d3dDevice8_->SetRenderState( D3DRS_LIGHTING , FALSE ) );
		DXASSERT( d3dDevice8_->SetVertexShader( D3DFVF_CUSTOMVERTEX ) );
		DXASSERT( d3dDevice8_->SetTextureStageState( 0 , D3DTSS_MIPFILTER , D3DTEXF_NONE ) );
		DXASSERT( d3dDevice8_->SetTextureStageState( 0, D3DTSS_MAGFILTER, D3DTEXF_NONE ) );
		DXASSERT( d3dDevice8_->SetTextureStageState( 0, D3DTSS_MINFILTER, D3DTEXF_NONE ) );
	}
	D3DDevice::~D3DDevice(){
		D3DDEVICE_CREATION_PARAMETERS param;
		d3dDevice8_->GetCreationParameters(&param);
		d3dDevice8_->Release();
		d3dDevice8_ = NULL;

		SetWindowPos( 
			param.hFocusWindow ,
			HWND_NOTOPMOST ,
			0 ,
			0 ,
			0 ,
			0 ,
			SWP_DRAWFRAME|SWP_NOMOVE|SWP_SHOWWINDOW|SWP_NOSIZE
		);
	}
	D3DTexture *D3DDevice::loadTexture( const std::string filename )const{
		LPDIRECT3DTEXTURE8 texture;
		D3DXIMAGE_INFO info;

		HRESULT hr = D3DXCreateTextureFromFileExA( d3dDevice8_ , // テクスチャーを作成するデバイス
													filename.c_str() , // 読み込むファイル名
													D3DX_DEFAULT , // 幅
													D3DX_DEFAULT  , // 高さ
													1 , // ミニマップレベル
													0 , // レンダリングターゲットOFF
													D3DFMT_UNKNOWN , // ファイルからカラーフォーマットを決定
													D3DPOOL_DEFAULT , // プールの方式
													D3DX_FILTER_NONE , // フィルタの方式
													D3DX_FILTER_NONE , // フィルタの方式
													0 , // カラーキーOFF
													&info , // 読み込んだイメージの情報
													NULL , // パレット情報
													&texture // テクスチャ
													);
		DXASSERT( hr );
		return new D3DTexture( texture , info );
	}
	D3DFont *D3DDevice::createFont( const int width , const int height , std::string fontname ){
		LPD3DXFONT	d3dFont      = NULL;

		HFONT hFont = CreateFont(
			height,           // 高さ
			width,           // 幅
			0,            // 文字送り方向の角度
			0,            // ベースラインの角度
			FW_NORMAL,// 太さ
			FALSE,        // 斜体かどうか
			FALSE,        // 下線を引くかどうか
			FALSE,        // 取り消し線
			SHIFTJIS_CHARSET,           // 文字セット
			OUT_DEFAULT_PRECIS,         // 出力精度
			CLIP_DEFAULT_PRECIS,        // クリッピング精度
			ANTIALIASED_QUALITY,        // 出力品質
			FIXED_PITCH | FF_SCRIPT,    // ピッチとファミリ
			fontname.c_str()          // フォント名
			);

		DXASSERT( D3DXCreateFont(d3dDevice8_, hFont, &d3dFont ) );
		DeleteObject(hFont);
		return new D3DFont( d3dFont );
	}
	void D3DDevice::renderBegin(){
		DXASSERT( d3dDevice8_->BeginScene() );

	}
	void D3DDevice::renderEnd(){
		DXASSERT( d3dDevice8_->EndScene() );
		DXASSERT( d3dDevice8_->Present( NULL , NULL , NULL , NULL ) );
	}
	void D3DDevice::render( const D3DTexture *texture , const float x , const float y , const float z ){
		static const float height = texture->getHeight();
		static const float width = texture->getWidth();
		static const float heightRatio = texture->getHeightRatio();
		static const float widthRatio = texture->getWidthRatio();
		static CUSTOMVERTEX cv[4] = {
			0.0f , 0.0f , 0.0f , 1.0f  , 0.0f , 0.0f ,
			0.0f , 0.0f , 0.0f , 1.0f  , 0.0f , 0.0f ,
			0.0f , 0.0f , 0.0f , 1.0f  , 0.0f , 0.0f ,
			0.0f , 0.0f , 0.0f , 1.0f  , 0.0f , 0.0f ,
		};
		cv[0].x = x;			cv[0].y = y;			cv[0].z = z; cv[0].tu =0.0;
		cv[1].x = x + width;	cv[1].y = y;			cv[1].z = z; cv[1].tu = widthRatio;
		cv[2].x = x + width;	cv[2].y = y + height;	cv[2].z = z; cv[2].tu = widthRatio; cv[2].tv = heightRatio;
		cv[3].x = x;			cv[3].y = y + height;	cv[3].z = z; cv[3].tv = heightRatio;

		d3dDevice8_->SetTexture( 0 , texture->texture_ );
		d3dDevice8_->DrawPrimitiveUP( D3DPT_TRIANGLELIST , 100 , cv  , sizeof CUSTOMVERTEX );
	}
	void D3DDevice::clear(){
		DXASSERT( d3dDevice8_->Clear( 0 , NULL , D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER , D3DCOLOR_XRGB( 128 , 0 , 0 ) , 1.0f , 0 ) );
	}
};