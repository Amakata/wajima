#pragma once

#include <d3d8.h>
#include <d3dx8.h>
#include "d3d.h"
#include "vertexbuffer.h"
#include <sstream>
#include <string>

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
			device_->SetRenderState( D3DRS_ZENABLE , D3DZB_TRUE   );
			device_->SetRenderState( D3DRS_LIGHTING , FALSE );
			device_->SetRenderState( D3DRS_ALPHAREF , 0 );
			device_->SetRenderState( D3DRS_ALPHAFUNC , D3DCMP_GREATER );
			device_->SetRenderState( D3DRS_ALPHATESTENABLE , TRUE );
			device_->SetRenderState( D3DRS_CULLMODE , TRUE );
			if( transparent ){
				device_->SetRenderState( D3DRS_ZWRITEENABLE , FALSE );
				device_->SetRenderState( D3DRS_ALPHABLENDENABLE , TRUE );
				device_->SetRenderState( D3DRS_SRCBLEND , D3DBLEND_SRCALPHA );
				device_->SetRenderState( D3DRS_DESTBLEND , D3DBLEND_DESTALPHA );
				device_->SetRenderState( D3DRS_BLENDOP , D3DBLENDOP_ADD );	
			}else{
				device_->SetRenderState( D3DRS_ZWRITEENABLE , TRUE );
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
			device_->BeginScene();
			device_->Clear( 0, NULL, D3DCLEAR_TARGET |D3DCLEAR_ZBUFFER  , D3DCOLOR_XRGB(0,128,0), 1.0f, 0 );
			device_->SetTexture( 0 , texture->texture_ );
			device_->SetStreamSource( 0 , buffer->vb_ , sizeof CUSTOMVERTEX );
			device_->DrawPrimitive( D3DPT_TRIANGLELIST , 0 , buffer->getSpriteSize()*2 );			
		}
	}
	void renderFont( std::string str , long left , long top , long right , long bottom   ){
		RECT rect = { left , top , right , bottom };
		if( font_ != NULL ){
			font_->Begin();
			font_->DrawTextA( str.c_str() , -1, &rect, DT_WORD_ELLIPSIS, 0xffffffff );
			font_->End();
		}
	}
	void present(){
		if( device_ != NULL ){
			device_->Present(NULL,NULL,NULL,NULL);
		}
	}
	std::string toString(){
		std::ostringstream oss;
		if( device_ != NULL ){
			LPDIRECT3D8 d3d;
			D3DADAPTER_IDENTIFIER8 identifier;
			device_->GetDirect3D(&d3d);
			d3d->GetAdapterIdentifier(D3DADAPTER_DEFAULT,0,&identifier);
			oss << identifier.Driver << " " << identifier.Description;
			d3d->Release();
			if(windowed_){
				oss << " " << "�i�E�B���h�E���[�h�j";
			}else{
				oss << " " << "�i�t���X�N���[�����[�h�j";
			}
			if(transparent_){
				oss << " " << "�i�������j";
			}else{
				oss << " " << "�i�s�����j";
			}
		}
		return oss.str();
	}
protected:
	void createDevice( HWND hWnd ,  LPDIRECT3D8 &d3d , bool windowed ){
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
		if( hr != D3D_OK ){
			hr = d3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &device_ );
		}
		if( hr != D3D_OK ){
			device_ = NULL;
		}
	}
	void setVertexShader(){
		if( device_ != NULL ){
			device_->SetVertexShader( D3DFVF_CUSTOMVERTEX );
		}
	}
	void setTextureStageState(){
		if( device_ != NULL ){
			device_->SetTextureStageState( 0 , D3DTSS_MIPFILTER , D3DX_FILTER_LINEAR );
			device_->SetTextureStageState( 0, D3DTSS_MAGFILTER, D3DX_FILTER_LINEAR );
			device_->SetTextureStageState( 0, D3DTSS_MINFILTER, D3DX_FILTER_LINEAR  );
			device_->SetTextureStageState( 0 , D3DTSS_ADDRESSU , D3DTADDRESS_BORDER );
			device_->SetTextureStageState( 0 , D3DTSS_ADDRESSV , D3DTADDRESS_BORDER );
		}
	}
	void createFont(){
		HFONT hFont = CreateFont(
			16,           // ����
			8,           // ��
			0,            // ������������̊p�x
			0,            // �x�[�X���C���̊p�x
			FW_NORMAL,// ����
			FALSE,        // �Α̂��ǂ���
			FALSE,        // �������������ǂ���
			FALSE,        // ��������
			SHIFTJIS_CHARSET,           // �����Z�b�g
			OUT_DEFAULT_PRECIS,         // �o�͐��x
			CLIP_DEFAULT_PRECIS,        // �N���b�s���O���x
			ANTIALIASED_QUALITY,        // �o�͕i��
			FIXED_PITCH | FF_SCRIPT,    // �s�b�`�ƃt�@�~��
			"�l�r �o����"          // �t�H���g��
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