#pragma once

#include <d3d8.h>
#include <d3dx8.h>
#include "d3d.h"
#include "vertexbuffer.h"
#include <sstream>
#include <string>
#include "Logger.h"

class Device {
public:
	Device( HWND hWnd , LPDIRECT3D8 &d3d , bool windowed ):device_(NULL),font_(NULL),hwnd_(hWnd),windowed_(windowed),transparent_(false),isSetRenderState_(false){
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
			DXERROR_LOG(device_->SetRenderState( D3DRS_SHADEMODE , D3DSHADE_FLAT ));
			DXERROR_LOG(device_->SetRenderState( D3DRS_ZENABLE , D3DZB_TRUE   ));
			DXERROR_LOG(device_->SetRenderState( D3DRS_LIGHTING , FALSE ));
			DXERROR_LOG(device_->SetRenderState( D3DRS_ALPHAREF , 0 ));
			DXERROR_LOG(device_->SetRenderState( D3DRS_ALPHAFUNC , D3DCMP_GREATER ));
			DXERROR_LOG(device_->SetRenderState( D3DRS_ALPHATESTENABLE , TRUE ));
			DXERROR_LOG(device_->SetRenderState( D3DRS_CULLMODE , D3DCULL_NONE ));
			DXERROR_LOG(device_->SetRenderState( D3DRS_COLORVERTEX , FALSE ));
			if( transparent ){
				DXERROR_LOG(device_->SetRenderState( D3DRS_ZWRITEENABLE , FALSE ));
				DXERROR_LOG(device_->SetRenderState( D3DRS_ALPHABLENDENABLE , TRUE ));
				DXERROR_LOG(device_->SetRenderState( D3DRS_SRCBLEND , D3DBLEND_SRCALPHA ));
				DXERROR_LOG(device_->SetRenderState( D3DRS_DESTBLEND , D3DBLEND_DESTALPHA ));
				DXERROR_LOG(device_->SetRenderState( D3DRS_BLENDOP , D3DBLENDOP_ADD  ));	
			}else{
				DXERROR_LOG(device_->SetRenderState( D3DRS_ZWRITEENABLE , TRUE ));
			}
			isSetRenderState_ = true;
		}
	}
	void printRenderState(){
		std::ofstream ofs;
		ofs.open("zefirobenchmarkoutput.txt", std::ios_base::out | std::ios_base::app );
		if( device_ != NULL ){
			if( windowed_ ){
				ofs << "ウィンドウモード ";
			}else{
				ofs << "フルスクリーンモード";
			}
			if( transparent_ ){
				ofs << "半透明 ";
			}else{
				ofs << "不透明 ";
			}
			if( isSetRenderState_ ){
				ofs << "設定済みレンダーステート";
			}else{
				ofs << "デフォルトレンダーステート";
			}
			ofs << std::endl;
			DWORD v;
			D3DLINEPATTERN pattern;
			float f;
			ofs << "D3DRS_ZENABLE = ";
			device_->GetRenderState( D3DRS_ZENABLE , &v );
			switch( v ){
				case D3DZB_FALSE:
					ofs << "D3DZB_FALSE";
					break;
				case D3DZB_TRUE:
					ofs << "D3DZB_TRUE";
					break;
				case D3DZB_USEW:
					ofs << "D3DZB_USEW";
					break;
			}
			ofs << std::endl;
			ofs << "D3DRS_FILLMODE = ";
			device_->GetRenderState( D3DRS_FILLMODE , &v );
			switch( v ){
				case D3DFILL_POINT:
					ofs << "D3DFILL_POINT";
					break;
				case D3DFILL_WIREFRAME:
					ofs << "D3DFILL_WIREFRAME";
					break;
				case D3DFILL_SOLID:
					ofs << " D3DFILL_SOLID";
					break;
			}
			ofs << std::endl;
			ofs << "D3DRS_SHADEMODE = ";
			device_->GetRenderState( D3DRS_SHADEMODE, &v );
			switch( v ){
				case D3DSHADE_FLAT:
					ofs << "D3DSHADE_FLAT";
					break;
				case D3DSHADE_GOURAUD:
					ofs << "D3DSHADE_GOURAUD";
					break;
				case D3DSHADE_PHONG:
					ofs << "D3DSHADE_PHONG";
					break;
			}
			ofs << std::endl;
			device_->GetRenderState( D3DRS_LINEPATTERN , (DWORD *)&pattern );
			ofs << "wRepeatPattern = " << pattern.wRepeatFactor << " wLinePattern = " << pattern.wLinePattern << std::endl;
			device_->GetRenderState( D3DRS_ZWRITEENABLE , &v );
			ofs << "D3DRS_ZWRITEENABLE = " << getBool( v ) << std::endl;
			device_->GetRenderState( D3DRS_ALPHATESTENABLE , &v );
			ofs << "D3DRS_ALPHATESTENABLE = " << getBool( v ) << std::endl;
			device_->GetRenderState( D3DRS_LASTPIXEL , &v );
			ofs << "D3DRS_LASTPIXEL = " << getBool( v ) << std::endl;
			ofs << "D3DRS_SRCBLEND = ";
			device_->GetRenderState( D3DRS_SRCBLEND , &v );
			ofs << getD3DBlend( v ) << std::endl;
			ofs << "D3DRS_DESTBLEND = ";
			device_->GetRenderState( D3DRS_DESTBLEND , &v );
			ofs << getD3DBlend( v ) << std::endl;
			ofs << "D3DRS_CULLMODE = ";
			device_->GetRenderState( D3DRS_CULLMODE , &v );
			switch( v ){
				case D3DCULL_NONE:
					ofs << "D3DCULL_NONE";
					break;
				case D3DCULL_CW:
					ofs << "D3DCULL_CW";
					break;
				case D3DCULL_CCW:
					ofs << "D3DCULL_CCW";
					break;
			}
			ofs << std::endl;
			ofs << "D3DRS_ZFUNC = ";
			device_->GetRenderState( D3DRS_ZFUNC , &v );
			ofs << getCmpFunc( v) << std::endl;
			device_->GetRenderState( D3DRS_ALPHAREF , &v );
			ofs << "D3DRS_ALPHAREF = " << v << std::endl;
			device_->GetRenderState( D3DRS_DITHERENABLE , &v );
			ofs << "D3DRS_DITHERENABLE = " << getBool(v) << std::endl;
			device_->GetRenderState( D3DRS_ALPHABLENDENABLE , &v );
			ofs << "D3DRS_ALPHABLENDENABLE = " << getBool(v) << std::endl;
			device_->GetRenderState( D3DRS_FOGENABLE , &v );
			ofs << "D3DRS_FOGENABLE = " << getBool(v) << std::endl;
			device_->GetRenderState( D3DRS_SPECULARENABLE , &v );
			ofs << "D3DRS_SPECULARENABLE = " << getBool(v) << std::endl;
			device_->GetRenderState( D3DRS_FOGCOLOR , &v );
			ofs << "D3DRS_FOGCOLOR = " << std::hex << v << std::dec << std::endl;
			device_->GetRenderState( D3DRS_FOGTABLEMODE , &v );
			ofs << "D3DRS_FOGTABLEMODE = " << getFogMode(v) << std::endl;
			device_->GetRenderState( D3DRS_FOGSTART , (DWORD*)&f );
			ofs <<  "D3DRS_FOGSTART = " << f << std::endl;
			device_->GetRenderState( D3DRS_FOGEND , (DWORD*)&f );
			ofs <<  "D3DRS_FOGEND = " << f << std::endl;
			device_->GetRenderState( D3DRS_FOGDENSITY , (DWORD*)&f );
			ofs <<  "D3DRS_FOGDENSITY = " << f << std::endl;
			device_->GetRenderState( D3DRS_EDGEANTIALIAS , &v );
			ofs << "D3DRS_EDGEANTIALIAS = " << getBool(v) << std::endl;
			device_->GetRenderState( D3DRS_ZBIAS , &v );
			ofs << "D3DRS_ZBIAS = " << v << std::endl;
			device_->GetRenderState( D3DRS_RANGEFOGENABLE , &v );
			ofs << "D3DRS_RANGEFOGENABLE = " << getBool(v) << std::endl;
			device_->GetRenderState( D3DRS_STENCILENABLE  , &v );
			ofs << "D3DRS_STENCILENABLE = " << getBool(v) << std::endl;
			device_->GetRenderState( D3DRS_STENCILFAIL , &v );
			ofs << "D3DRS_STENCILFAIL = " << getStencilop(v) << std::endl;
			device_->GetRenderState( D3DRS_STENCILZFAIL , &v );
			ofs << "D3DRS_STENCILZFAIL = " << getStencilop(v) << std::endl;
			device_->GetRenderState( D3DRS_STENCILPASS , &v );
			ofs << "D3DRS_STENCILPASS = " << getStencilop(v) << std::endl;
			device_->GetRenderState( D3DRS_STENCILFUNC , &v );
			ofs << "D3DRS_STENCILFUNC = " << getCmpFunc(v) << std::endl;
			device_->GetRenderState( D3DRS_STENCILREF , &v );
			ofs << "D3DRS_STENCILREF = " << v << std::endl;
			device_->GetRenderState( D3DRS_STENCILMASK , &v );
			ofs << "D3DRS_STENCILMASK = " << std::hex << v << std::dec << std::endl;
			device_->GetRenderState( D3DRS_STENCILWRITEMASK , &v );
			ofs << "D3DRS_STENCILWRITEMASK = " << std::hex << v << std::dec << std::endl;
			device_->GetRenderState( D3DRS_TEXTUREFACTOR , &v );
			ofs << "D3DRS_TEXTUREFACTOR = " << std::hex << v << std::dec << std::endl;
			device_->GetRenderState( D3DRS_WRAP0 , &v );
			ofs << "D3DRS_WRAP0 = " << getWrap(v) << std::endl;
			device_->GetRenderState( D3DRS_CLIPPING , &v );
			ofs << "D3DRS_CLIPPING = " << getBool(v) << std::endl;
			device_->GetRenderState( D3DRS_LIGHTING , &v );
			ofs << "D3DRS_LIGHTING = " << getBool(v) << std::endl;
			device_->GetRenderState( D3DRS_AMBIENT , &v );
			ofs << "D3DRS_AMBIENT = " << std::hex << v << std::dec << std::endl;
			device_->GetRenderState( D3DRS_FOGVERTEXMODE  , &v );
			ofs << "D3DRS_FOGVERTEXMODE = " << getFogMode(v) << std::endl;
			device_->GetRenderState( D3DRS_COLORVERTEX , &v );
			ofs << "D3DRS_COLORVERTEX = " << getBool(v) << std::endl;
			device_->GetRenderState( D3DRS_LOCALVIEWER , &v );
			ofs << "D3DRS_LOCLAVIEWR = " << getBool(v) << std::endl;
			device_->GetRenderState( D3DRS_NORMALIZENORMALS , &v );
			ofs << "D3DRS_NORMALIZENORMALS = " << getBool(v) << std::endl;
			device_->GetRenderState( D3DRS_DIFFUSEMATERIALSOURCE , &v );
			ofs << "D3DRS_DIFFUSEMATERIALSOURCE = " << getMaterialColorSource(v) << std::endl;
			device_->GetRenderState( D3DRS_SPECULARMATERIALSOURCE , &v );
			ofs << "D3DRS_SPECULARMATERIALSOURCE = " << getMaterialColorSource(v) << std::endl;
			device_->GetRenderState( D3DRS_AMBIENTMATERIALSOURCE , &v );
			ofs << "D3DRS_AMBIENTMATERIALSOURCE = " << getMaterialColorSource(v) << std::endl;
			device_->GetRenderState( D3DRS_EMISSIVEMATERIALSOURCE , &v );
			ofs << "D3DRS_EMISSIVEMATERIALSOURCE = " << getMaterialColorSource(v) << std::endl;
			device_->GetRenderState(  D3DRS_VERTEXBLEND , &v );
			ofs << "D3DRS_VERTEXBLEND = ";
			switch( v ){
				case D3DVBF_DISABLE:
					ofs << "D3DVBF_DISABLE";
					break;
				case D3DVBF_1WEIGHTS:
					ofs << "D3DVBF_1WEIGHTS";
					break;
				case D3DVBF_2WEIGHTS:
					ofs << "D3DVBF_2WEIGHTS";
					break;
				case D3DVBF_3WEIGHTS:
					ofs << "D3DVBF_3WEIGHTS";
					break;
				case D3DVBF_TWEENING:
					ofs << "D3DVBF_TWEENING";
					break;
				case D3DVBF_0WEIGHTS:
					ofs << "D3DVBF_0WEIGHTS";
					break;
			}
			ofs << std::endl;
			device_->GetRenderState( D3DRS_CLIPPLANEENABLE, &v );
			ofs << "D3DRS_CLIPPLANEENABLE = " << std::hex << v << std::dec << std::endl;
			device_->GetRenderState( D3DRS_SOFTWAREVERTEXPROCESSING , &v );
			ofs << "D3DRS_SOFTWAREVERTEXPROCESSING = " << getBool(v) << std::endl;
			device_->GetRenderState( D3DRS_POINTSIZE , (DWORD*)&f );
			ofs << "D3DRS_POINTSIZE = " << f << std::endl;
			device_->GetRenderState( D3DRS_POINTSIZE_MIN , (DWORD*)&f );
			ofs << "D3DRS_POINTSIZE_MIN = " << f << std::endl;
			device_->GetRenderState( D3DRS_POINTSIZE_MAX , (DWORD*)&f );
			ofs << "D3DRS_POINTSIZE_MAX = " << f << std::endl;
			device_->GetRenderState( D3DRS_POINTSPRITEENABLE , &v );
			ofs << "D3DRS_POINTSPRITEENABLE = " << getBool(v) << std::endl;
			device_->GetRenderState( D3DRS_POINTSCALEENABLE , &v );
			ofs << "D3DRS_POINTSCALEENABLE = " << getBool(v) << std::endl;
			device_->GetRenderState( D3DRS_POINTSCALE_A , (DWORD*)&f );
			ofs << "D3DRS_POINTSCALE_A = " << f << std::endl;
			device_->GetRenderState( D3DRS_POINTSCALE_B , (DWORD*)&f );
			ofs << "D3DRS_POINTSCALE_B = " << f << std::endl;
			device_->GetRenderState( D3DRS_POINTSCALE_C , (DWORD*)&f );
			ofs << "D3DRS_POINTSCALE_C = " << f << std::endl;
			device_->GetRenderState( D3DRS_MULTISAMPLEANTIALIAS , &v );
			ofs << "D3DRS_MULTISAMPLEANTIALIAS = " << getBool(v) << std::endl;
			device_->GetRenderState( D3DRS_MULTISAMPLEMASK, &v );
			ofs << "D3DRS_MULTISAMPLEMASK = " << std::hex << v << std::dec << std::endl;
			device_->GetRenderState( D3DRS_PATCHEDGESTYLE , &v );
			ofs << "D3DRS_PATCHEDGESTYLE = ";
			switch( v ){
				case D3DPATCHEDGE_DISCRETE:
					ofs << "D3DPATCHEDGE_DISCRETE";
					break;
				case D3DPATCHEDGE_CONTINUOUS:
					ofs << "D3DPATCHEDGE_CONTINUOUS";
					break;
			}
			ofs << std::endl;
			device_->GetRenderState( D3DRS_PATCHSEGMENTS , (DWORD*)&f );
			ofs << "D3DRS_PATCHSEGMENTS = " << f << std::endl;
			device_->GetRenderState( D3DRS_DEBUGMONITORTOKEN , &v );
			ofs << "D3DRS_DEBUGMONITORTOKEN = ";
			switch( v ){
				case D3DDMT_ENABLE:
					ofs << "D3DDMT_ENABLE";
					break;
				case D3DDMT_DISABLE:
					ofs << "D3DDMT_DISABLE";
					break;
				default:
					ofs << "ERROR";
					break;
			}
			ofs << std::endl;
			device_->GetRenderState( D3DRS_INDEXEDVERTEXBLENDENABLE , &v );
			ofs << "D3DRS_INDEXEDVERTEXBLENDENABLE = " << getBool(v) << std::endl;
			device_->GetRenderState( D3DRS_COLORWRITEENABLE , &v );
			ofs << "D3DRS_COLORWRITEENABLE = " << std::hex << v << std::dec << std::endl;
			device_->GetRenderState( D3DRS_TWEENFACTOR , (DWORD*)&f );
			ofs << "D3DRS_TWEENFACTOR = " << f << std::endl;
			device_->GetRenderState( D3DRS_BLENDOP , &v );
			ofs << "D3DRS_BLENDOP = " << getD3DBlend( v ) << std::endl;

		}
		ofs.close();
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
			hr = d3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &device_ );
			DXERROR_LOG( hr );
		}
		if( hr != D3D_OK ){
			hr = d3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &device_ );
			DXERROR_LOG( hr );
		}
		d3dpp.BackBufferFormat = D3DFMT_R8G8B8;
		if( hr != D3D_OK ){
			hr = d3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &device_ );
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
		d3dpp.BackBufferFormat = D3DFMT_R5G6B5;
		if( hr != D3D_OK ){
			hr = d3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &device_ );
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
		d3dpp.BackBufferFormat = D3DFMT_X1R5G5B5;
		if( hr != D3D_OK ){
			hr = d3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &device_ );
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
			DXERROR_LOG(device_->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_SELECTARG1 ));
			DXERROR_LOG(device_->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE));
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
	std::string getD3DBlend( DWORD v ){
		std::ostringstream oss;
		switch( v ){
		case D3DBLEND_ZERO :
			oss << "D3DBLEND_ZERO";
			break;
		case D3DBLEND_ONE:
			oss << "D3DBLEND_ONE";
			break;
		case D3DBLEND_SRCCOLOR:
			oss << "D3DBLEND_SRCCOLOR";
			break;
		case D3DBLEND_INVSRCCOLOR:
			oss << "D3DBLEND_INVSRCCOLOR";
			break;
		case D3DBLEND_SRCALPHA:
			oss << "D3DBLEND_SRCALPHA";
			break;
		case D3DBLEND_INVSRCALPHA:
			oss << "D3DBLEND_INVSRCALPHA";
			break;
		case D3DBLEND_DESTALPHA:
			oss << "D3DBLEND_DESTALPHA";
			break;
		case D3DBLEND_INVDESTALPHA:
			oss << "D3DBLEND_INVDESTALPHA";
			break;
		case D3DBLEND_DESTCOLOR:
			oss << "D3DBLEND_DESTCOLOR";
			break;
		case D3DBLEND_INVDESTCOLOR:
			oss << "D3DBLEND_INVDESTCOLOR";
			break;
		case D3DBLEND_SRCALPHASAT :
			oss << "D3DBLEND_SRCALPHASAT ";
			break;
		case D3DBLEND_BOTHSRCALPHA:
			oss << "D3DBLEND_BOTHSRCALPHA";
			break;
		case D3DBLEND_BOTHINVSRCALPHA:
			oss << "D3DBLEND_BOTHINVSRCALPHA";
			break;
		}
		return oss.str();
	}
	std::string getCmpFunc( DWORD v ){
		std::ostringstream oss;
		switch( v ){
			case D3DCMP_NEVER:
				oss << "D3DCMP_NEVER";
				break;
			case D3DCMP_LESS:
				oss << "D3DCMP_LESS";
				break;
			case D3DCMP_EQUAL:
				oss << "D3DCMP_EQUAL";
				break;
			case D3DCMP_LESSEQUAL:
				oss << "D3DCMP_LESSEQUAL";
				break;
			case D3DCMP_GREATER:
				oss << "D3DCMP_GREATER";
				break;
			case D3DCMP_NOTEQUAL:
				oss << "D3DCMP_NOTEQUAL";
				break;
			case D3DCMP_GREATEREQUAL:
				oss << "D3DCMP_GREATEREQUAL";
				break;
			case D3DCMP_ALWAYS:
				oss << "D3DCMP_ALWAYS";
				break;
		}
		return oss.str();
	}
	std::string getBool( DWORD v ){
		if( v == TRUE ){
			return std::string("TRUE");
		}else{
			return std::string("FALSE");
		}
	}
	std::string getStencilop( DWORD v ){
		switch(v){
			case D3DSTENCILOP_KEEP:
				return std::string("D3DSTENCILOP_KEEP");
			case D3DSTENCILOP_ZERO:
				return std::string("D3DSTENCILOP_ZERO");
			case D3DSTENCILOP_REPLACE:
				return std::string("D3DSTENCILOP_REPLACE");
			case D3DSTENCILOP_INCRSAT:
				return std::string("D3DSTENCILOP_INCRSAT");
			case D3DSTENCILOP_DECRSAT:
				return std::string("D3DSTENCILOP_DECRSAT");
			case D3DSTENCILOP_INVERT:
				return std::string("D3DSTENCILOP_INVERT");
			case D3DSTENCILOP_INCR:
				return std::string("D3DSTENCILOP_INCR");
			case D3DSTENCILOP_DECR:
				return std::string("D3DSTENCILOP_DECR");
			default:
				return "";
		}
	}
	std::string getWrap( DWORD v ){
		std::ostringstream oss;
		
		if( v & D3DWRAPCOORD_0 ){
			oss << "D3DWRAP_U ";
		}
		if( v & D3DWRAPCOORD_1 ){
			oss << "D3DWRAP_V ";
		}
		if( v & D3DWRAPCOORD_2 ){
			oss << "D3DWRAP_W ";
		}
		if( v & D3DWRAPCOORD_3 ){
			oss << "D3DWRAP_X ";
		}
		return oss.str();
	}
	std::string getFogMode( DWORD v ){
		switch( v ){
			case D3DFOG_NONE:
				return "D3DFOG_NONE";
			case D3DFOG_EXP:
				return "D3DFOG_EXP";
			case D3DFOG_EXP2:
				return  "D3DFOG_EXP2";
			case D3DFOG_LINEAR:
				return "D3DFOG_LINEAR";
			default:
				return "";
		}
	}
	std::string getMaterialColorSource( DWORD v ){
		switch( v ){
			case D3DMCS_MATERIAL:
				return "D3DMCS_MATERIAL";
			case D3DMCS_COLOR1:
				return "D3DMCS_COLOR1";
			case D3DMCS_COLOR2:
				return "D3DMCS_COLOR2";
			default:
				return "";
		}
	}
	LPDIRECT3DDEVICE8 device_;
	LPD3DXFONT		  font_;
	HWND	hwnd_;
	bool windowed_;
	bool transparent_;
	bool isSetRenderState_;
};