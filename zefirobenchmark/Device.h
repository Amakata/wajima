#pragma once

#include <d3d8.h>
#include <d3dx8.h>
#include "d3d.h"
#include "vertexbuffer.h"
#include <sstream>
#include <string>


#define DXERROR_LOG( hr )	{	HRESULT hr2 = hr; if( hr2 != D3D_OK ){std::ofstream ofs;	ofs.open("error_log",std::ios_base::out | std::ios_base::app ); ofs <<__FILE__<<":"<<__LINE__<<":"<<hr2<< std::endl; ofs.close();} }

class Device {
public:
	Device( HWND hWnd , LPDIRECT3D8 &d3d , bool windowed ):device_(NULL),font_(NULL),hwnd_(hWnd),windowed_(windowed),transparent_(false){
		createDevice( hWnd , d3d , windowed );
		setVertexShader();
		setTextureStageState();
		createFont();
	}
	virtual ~Device(){
		releaseFont();
		if( device_ != NULL ){
			device_->Release();
			device_ = NULL;
		}
		SetWindowPos( 
			hwnd_ ,
			HWND_TOP ,
			0 ,
			0 ,
			DISPLAY_WIDTH + GetSystemMetrics(SM_CYFRAME)*2 ,
			DISPLAY_HEIGHT + GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYMENU) + GetSystemMetrics(SM_CYFRAME)*2 ,
			SWP_DRAWFRAME|SWP_NOMOVE|SWP_SHOWWINDOW 
		);
	}
	void setRenderState( bool transparent ){
		if( device_ != NULL ){
			transparent_ = transparent;
			DXERROR_LOG(device_->SetRenderState( D3DRS_ZENABLE , D3DZB_TRUE   ));
			DXERROR_LOG(device_->SetRenderState( D3DRS_LIGHTING , FALSE ));
			DXERROR_LOG(device_->SetRenderState( D3DRS_ALPHAREF , 0 ));
			DXERROR_LOG(device_->SetRenderState( D3DRS_ALPHAFUNC , D3DCMP_GREATER ));
			DXERROR_LOG(device_->SetRenderState( D3DRS_ALPHATESTENABLE , TRUE ));
			DXERROR_LOG(device_->SetRenderState( D3DRS_CULLMODE , TRUE ));
			if( transparent ){
				DXERROR_LOG(device_->SetRenderState( D3DRS_ZWRITEENABLE , FALSE ));
				DXERROR_LOG(device_->SetRenderState( D3DRS_ALPHABLENDENABLE , TRUE ));
				DXERROR_LOG(device_->SetRenderState( D3DRS_SRCBLEND , D3DBLEND_SRCALPHA ));
				DXERROR_LOG(device_->SetRenderState( D3DRS_DESTBLEND , D3DBLEND_DESTALPHA ));
				DXERROR_LOG(device_->SetRenderState( D3DRS_BLENDOP , D3DBLENDOP_ADD ));	
			}else{
				DXERROR_LOG(device_->SetRenderState( D3DRS_ZWRITEENABLE , TRUE ));
			}
		}
	}
	VertexBuffer *createVertexBuffer( int spriteSize ){
		return new VertexBuffer( device_ , spriteSize );

	}
	Texture *createTexture( std::string filename ){
		return new Texture( device_ , filename );
	}
	void render( VertexBuffer *buffer , Texture *texture){
		if( device_ != NULL ){
			DXERROR_LOG(device_->BeginScene());
			DXERROR_LOG(device_->Clear( 0, NULL, D3DCLEAR_TARGET |D3DCLEAR_ZBUFFER  , D3DCOLOR_XRGB(0,128,0), 1.0f, 0 ));
			DXERROR_LOG(device_->SetTexture( 0 , texture->texture_ ));
			DXERROR_LOG(device_->SetStreamSource( 0 , buffer->vb_ , sizeof CUSTOMVERTEX ));
			DXERROR_LOG(device_->DrawPrimitive( D3DPT_TRIANGLELIST , 0 , buffer->getSpriteSize()*2 ));
			DXERROR_LOG(device_->EndScene());
		}
	}
	void renderFont( std::string str , long left , long top , long right , long bottom   ){
		RECT rect = { left , top , right , bottom };
		if( font_ != NULL ){
			DXERROR_LOG(font_->Begin());
			font_->DrawText( str.c_str() , -1, &rect, DT_WORD_ELLIPSIS, 0xffffffff );
			DXERROR_LOG(font_->End());
		}
	}
	void present(){
		if( device_ != NULL ){
			DXERROR_LOG(device_->Present(NULL,NULL,NULL,NULL));
		}
	}
	std::string toString(){
		std::ostringstream oss;
		if( device_ != NULL ){
			LPDIRECT3D8 d3d;
			D3DADAPTER_IDENTIFIER8 identifier;
			DXERROR_LOG(device_->GetDirect3D(&d3d));
			DXERROR_LOG(d3d->GetAdapterIdentifier(D3DADAPTER_DEFAULT,0,&identifier));
			oss << identifier.Driver << " " << identifier.Description;
			d3d->Release();
			if(windowed_){
				oss << " " << "（ウィンドウモード）";
			}else{
				oss << " " << "（フルスクリーンモード）";
			}
			if(transparent_){
				oss << " " << "（半透明）";
			}else{
				oss << " " << "（不透明）";
			}
		}
		return oss.str();
	}
	bool isAvailable(){
		return device_ != NULL;
	}
protected:
	void createDevice( HWND hWnd ,  LPDIRECT3D8 &d3d , bool windowed ){
		D3DDISPLAYMODE mode;
		DXERROR_LOG(d3d->GetAdapterDisplayMode( D3DADAPTER_DEFAULT , &mode ));
		if( mode.Format != D3DFMT_X8R8G8B8 && windowed ){
			MessageBox( hWnd , "ウィンドウモードで実行する場合は２４ビットモードで実行してください。","お願い",MB_OK);
			return;
		}
		D3DPRESENT_PARAMETERS d3dpp;
		ZeroMemory( &d3dpp, sizeof(d3dpp) );
		d3dpp.Windowed   = windowed;
		d3dpp.SwapEffect =   D3DSWAPEFFECT_DISCARD;
		d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
		d3dpp.BackBufferHeight = DISPLAY_HEIGHT;
		d3dpp.BackBufferWidth = DISPLAY_WIDTH;
		d3dpp.EnableAutoDepthStencil = TRUE;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
		d3dpp.BackBufferCount = 1;
		HRESULT hr;
		hr = d3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &device_ );
		DXERROR_LOG( hr );
		if( hr != D3D_OK ){
			hr = d3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &device_ );
			DXERROR_LOG( hr );
		}
		if( hr != D3D_OK ){
			hr = d3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &device_ );
			DXERROR_LOG( hr );
		}
		if( hr != D3D_OK ){
			hr = d3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &device_ );
			DXERROR_LOG( hr );
		}
		if( hr != D3D_OK ){
			MessageBox( hWnd , "グラフィックの初期化に失敗しました。","エラー",MB_OK);
			device_ = NULL;
		}
	}
	void setVertexShader(){
		if( device_ != NULL ){
			HRESULT hr =device_->SetVertexShader( D3DFVF_CUSTOMVERTEX );
			DXERROR_LOG( hr );
		}
	}
	void setTextureStageState(){
		if( device_ != NULL ){
			DXERROR_LOG(device_->SetTextureStageState( 0 , D3DTSS_MIPFILTER , D3DX_FILTER_LINEAR ));
			DXERROR_LOG(device_->SetTextureStageState( 0, D3DTSS_MAGFILTER, D3DX_FILTER_LINEAR ));
			DXERROR_LOG(device_->SetTextureStageState( 0, D3DTSS_MINFILTER, D3DX_FILTER_LINEAR  ));
			DXERROR_LOG(device_->SetTextureStageState( 0 , D3DTSS_ADDRESSU , D3DTADDRESS_BORDER ));
			DXERROR_LOG(device_->SetTextureStageState( 0 , D3DTSS_ADDRESSV , D3DTADDRESS_BORDER ));
		}
	}
	void createFont(){
		HFONT hFont = CreateFont(
			16,           // 高さ
			8,           // 幅
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
			"ＭＳ Ｐ明朝"          // フォント名
			);
		D3DXCreateFont(device_, hFont, &font_ );
		DeleteObject(hFont);
	}
	void releaseFont(){
		if( font_ != NULL ){
			font_->Release();
		}
	}
	LPDIRECT3DDEVICE8 device_;
	LPD3DXFONT		  font_;
	HWND	hwnd_;
	bool windowed_;
	bool transparent_;
};