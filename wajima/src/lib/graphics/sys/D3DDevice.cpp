/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/graphics/sys/Attic/D3DDevice.cpp,v 1.9 2002/10/29 14:10:34 ama Exp $
 */

#include "graphics/sys/D3DDevice.h"
#include "graphics/sys/DXAssert.h"
#include <d3dx8tex.h>
#include "std/Logger.h"
#include <sstream>

#define D3DFVF_CUSTOMVERTEX	(D3DFVF_XYZRHW|D3DFVF_TEX1)

namespace zefiro_graphics {
	D3DDevice::D3DDevice( LPDIRECT3DDEVICE8 d3ddevice8 ):
		device_(d3ddevice8),
		numOfSprite_(0),numOfTransparentSprite_(0),
		vbOfSprites_(NULL),vbOfTransparentSprites_(NULL){

		getDeviceCapability();
		setDefaultRenderState();
		setDefaultTextureStageState();
		DXASSERT( device_->SetVertexShader( D3DFVF_CUSTOMVERTEX ) );
	}
	D3DDevice::~D3DDevice(){
		D3DDEVICE_CREATION_PARAMETERS param;
		DXASSERT(device_->GetCreationParameters(&param));
		DXASSERT(device_->Release());
		device_ = NULL;

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

		HRESULT hr = D3DXCreateTextureFromFileExA( device_ , // �e�N�X�`���[���쐬����f�o�C�X
													filename.c_str() , // �ǂݍ��ރt�@�C����
													D3DX_DEFAULT , // ��
													D3DX_DEFAULT  , // ����
													1 , // �~�j�}�b�v���x��
													0 , // �����_�����O�^�[�Q�b�gOFF
													D3DFMT_UNKNOWN , // �t�@�C������J���[�t�H�[�}�b�g������
													D3DPOOL_DEFAULT , // �v�[���̕���
													D3DX_FILTER_NONE , // �t�B���^�̕���
													D3DX_FILTER_NONE , // �t�B���^�̕���
													0 , // �J���[�L�[OFF
													&info , // �ǂݍ��񂾃C���[�W�̏��
													NULL , // �p���b�g���
													&texture // �e�N�X�`��
													);
		DXASSERT( hr );
		return new D3DTexture( texture , info );
	}
	D3DFont *D3DDevice::createFont( const int width , const int height , std::string fontname ){
		LPD3DXFONT	d3dFont      = NULL;

		HFONT hFont = CreateFont(
			height,           // ����
			width,           // ��
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
			fontname.c_str()          // �t�H���g��
			);

		DXASSERT( D3DXCreateFont(device_, hFont, &d3dFont ) );
		DeleteObject(hFont);
		return new D3DFont( d3dFont );
	}
	void D3DDevice::clear(){
		DXASSERT( device_->Clear( 0 , NULL , D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER , D3DCOLOR_XRGB( 0 , 0 , 0 ) , 1.0f , 0 ) );
	}
	void D3DDevice::render(){
		DXASSERT( device_->BeginScene() );		


		device_->SetTexture( 0 , texture->first->texture_ );
		device_->DrawPrimitiveUP( D3DPT_TRIANGLELIST , numOfSprites * 2 , pV , sizeof CUSTOMVERTEX );
		DXASSERT( device_->EndScene() );
		if( vbOfSprites_ != NULL ){
			DXASSERT( vbOfSprites_->Release() );
			vbOfSprites_ = NULL;
		}
		if( vbOfTransparentSprites_ != NULL ){
			DXASSERT( vbOfTransparentSprites_->Release() );
			vbOfTransparentSprites_ = NULL;
		}
	}
	void D3DDevice::setBegin(){
		sprites_.clear();
		transparentSprites_.clear();
	}
	void D3DDevice::setSprite( const D3DTexture* texture , const float x , const float y , const float z , const bool transparent ){
		if( transparent ){
			transparentSprites_[ (LPD3DTEXTURE)texture ].push_back( D3DXVECTOR3(x,y,z) );
			++numOfTransparentSprite_;
		}else{
			sprites_[ (LPD3DTEXTURE)texture ].push_back( D3DXVECTOR3(x,y,z) );
			++numOfSprite_;
		}
	}
	void D3DDevice::setEnd(){
		if( vbOfSprites_ == NULL ){
			DXASSERT( device_->CreateVertexBuffer( sizeof(CUSTOMVERTEX) * numOfSprite_ * 6 , D3DUSAGE_WRITEONLY , D3DFVF_CUSTOMVERTEX , D3DPOOL_MANAGED , &vbOfSprites_ ) );
		}
		


		if( vbOfTransparentSprites_ == NULL ){
			DXASSERT( device_->CreateVertexBuffer( sizeof(CUSTOMVERTEX) * numOfTransparentSprite_ * 6 , D3DUSAGE_WRITEONLY , D3DFVF_CUSTOMVERTEX , D3DPOOL_MANAGED , &vbOfTransparentSprites_ ) );
		}

	}
	void D3DDevice::present(){
		DXASSERT( device_->Present( NULL , NULL , NULL , NULL ) );
	}
	void D3DDevice::getDeviceCapability(){
		DXASSERT( device_->GetDeviceCaps( &caps_ ) );
	}
	void D3DDevice::setDefaultRenderState(){
		DXASSERT( device_->SetRenderState( D3DRS_ZENABLE  , D3DZB_TRUE ) );
		DXASSERT( device_->SetRenderState( D3DRS_ZWRITEENABLE , TRUE ) );
		DXASSERT( device_->SetRenderState( D3DRS_CULLMODE , D3DCULL_NONE ) );
		DXASSERT( device_->SetRenderState( D3DRS_LIGHTING , FALSE ) );
		DXASSERT( device_->SetRenderState( D3DRS_ALPHAREF , 0 ) );
		DXASSERT( device_->SetRenderState( D3DRS_ALPHAFUNC , D3DCMP_GREATEREQUAL ) );
		DXASSERT( device_->SetRenderState( D3DRS_ALPHABLENDENABLE , FALSE ) );
		DXASSERT( device_->SetRenderState( D3DRS_ALPHATESTENABLE , TRUE ) );
		DXASSERT( device_->SetRenderState( D3DRS_SHADEMODE , D3DSHADE_FLAT ) );
	}
	void D3DDevice::setDefaultTextureStageState(){
		DXASSERT( device_->SetTextureStageState( 0 , D3DTSS_MIPFILTER , D3DTEXF_NONE ) );
		DXASSERT( device_->SetTextureStageState( 0, D3DTSS_MAGFILTER, D3DTEXF_NONE ) );
		DXASSERT( device_->SetTextureStageState( 0, D3DTSS_MINFILTER, D3DTEXF_NONE ) );
	}
};