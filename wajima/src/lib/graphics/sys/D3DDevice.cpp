/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/graphics/sys/Attic/D3DDevice.cpp,v 1.5 2002/09/18 18:02:34 ama Exp $
 */

#include "graphics/sys/D3DDevice.h"
#include "graphics/sys/DXAssert.h"
#include <d3dx8tex.h>
#include "std/Logger.h"
#include <sstream>
typedef struct CUSTOMVERTEX_ {
	float x,y,z,rhw;
	DWORD color;
	float tu,tv;
}CUSTOMVERTEX;

#define D3DFVF_CUSTOMVERTEX	(D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)

namespace zefiro_graphics {
	D3DDevice::D3DDevice( LPDIRECT3DDEVICE8 d3ddevice8 ):d3dDevice8_(d3ddevice8){
	}
	D3DDevice::~D3DDevice(){
		d3dDevice8_->Release();
		d3dDevice8_ = NULL;
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
	void D3DDevice::renderBegin(){
		DXASSERT( d3dDevice8_->BeginScene() );
		d3dDevice8_->SetRenderState( D3DRS_ZENABLE  , D3DZB_TRUE );
		d3dDevice8_->SetRenderState( D3DRS_ZWRITEENABLE , TRUE );
		d3dDevice8_->SetRenderState( D3DRS_ALPHAREF , 0 );
		d3dDevice8_->SetRenderState( D3DRS_ALPHATESTENABLE , TRUE );
		d3dDevice8_->SetRenderState( D3DRS_ALPHAFUNC , D3DCMP_GREATEREQUAL );
		d3dDevice8_->SetRenderState( D3DRS_ALPHABLENDENABLE , TRUE );
		d3dDevice8_->SetRenderState( D3DRS_SRCBLEND , D3DBLEND_SRCALPHA );
		d3dDevice8_->SetRenderState( D3DRS_DESTBLEND , D3DBLEND_INVSRCALPHA );
		d3dDevice8_->SetVertexShader( D3DFVF_CUSTOMVERTEX );
	}
	void D3DDevice::renderEnd(){
		DXASSERT( d3dDevice8_->EndScene() );
		DXASSERT( d3dDevice8_->Present( NULL , NULL , NULL , NULL ) );
	}
	void D3DDevice::render( const D3DTexture *texture , float x , float y , float z ){
		CUSTOMVERTEX cv[4] = {
			x						+0.5f, y -0.5f							, z , 1.0f , 0xFFFFFFFF , 0.0f , 0.0f ,
			x + texture->getWidth() +0.5f, y -0.5f							, z , 1.0f , 0xFFFFFFFF , texture->getWidthRatio() , 0.0f ,
			x + texture->getWidth() +0.5f, y + texture->getHeight()	-0.5f, z , 1.0f , 0xFFFFFFFF , texture->getWidthRatio()  , texture->getHeightRatio() ,
			x						+0.5f, y + texture->getHeight()	-0.5f, z , 1.0f , 0xFFFFFFFF , 0.0f , texture->getWidthRatio() 
		};
		d3dDevice8_->SetTexture( 0 , texture->texture_ );
		d3dDevice8_->DrawPrimitiveUP( D3DPT_TRIANGLEFAN , 2 , cv  , sizeof CUSTOMVERTEX );
	}
	void D3DDevice::clear(){
		DXASSERT( d3dDevice8_->Clear( 0 , NULL , D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER , D3DCOLOR_XRGB( 128 , 0 , 0 ) , 1.0f , 0 ) );
	}
};