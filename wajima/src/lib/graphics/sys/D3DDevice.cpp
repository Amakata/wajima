/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/graphics/sys/Attic/D3DDevice.cpp,v 1.2 2002/09/13 05:36:08 ama Exp $
 */

#include "graphics/sys/D3DDevice.h"
#include "graphics/sys/DXAssert.h"
#include <d3dx8tex.h>

namespace zefiro_graphics {
	D3DDevice::D3DDevice( LPDIRECT3DDEVICE8 d3ddevice8 , LPD3DXSPRITE d3dsprite ):D3DDevice8_(d3ddevice8),D3DSprite_(d3dsprite){
		D3DDevice8_->SetRenderState( D3DRS_ZENABLE  , D3DZB_TRUE );
		D3DDevice8_->SetRenderState( D3DRS_ZWRITEENABLE , TRUE );
	}
	D3DDevice::~D3DDevice(){
		D3DSprite_->Release();
		D3DDevice8_->Release();
	}
	D3DTexture *D3DDevice::loadTexture( const std::string filename )const{
		LPDIRECT3DTEXTURE8 texture;
		HRESULT hr = D3DXCreateTextureFromFileExA( D3DDevice8_ , // �e�N�X�`���[���쐬����f�o�C�X
													filename.c_str() , // �ǂݍ��ރt�@�C����
													D3DX_DEFAULT , // ��
													D3DX_DEFAULT  , // ����
													1 , // �g�Ƀ}�b�v���x��
													0 , // �����_�����O�^�[�Q�b�gOFF
													D3DFMT_UNKNOWN , // �t�@�C������J���[�t�H�[�}�b�g������
													D3DPOOL_DEFAULT , // �v�[���̕���
													D3DX_FILTER_NONE , // �t�B���^�̕���
													D3DX_FILTER_NONE , // �t�B���^�̕���
													0 , // �J���[�L�[OFF
													NULL , // �ǂݍ��񂾃C���[�W�̏��
													NULL , // �p���b�g���
													&texture // �e�N�X�`��
													);
		DXASSERT( hr );
		return new D3DTexture( texture );
	}
	void D3DDevice::renderBegin(){
		DXASSERT( D3DDevice8_->BeginScene() );
		DXASSERT( D3DSprite_->Begin() );
	}
	void D3DDevice::renderEnd(){
		DXASSERT( D3DSprite_->End() );
		DXASSERT( D3DDevice8_->EndScene() );
		DXASSERT( D3DDevice8_->Present( NULL , NULL , NULL , NULL ) );
	}
	void D3DDevice::render( const D3DTexture *texture , float x , float y , float z ){
		D3DXMATRIX d3dxMatrix(
								1.0 , 0.0 , 0.0 , 0.0 ,
								0.0 , 1.0 , 0.0 , 0.0 ,
								0.0 , 0.0 , 1.0 , 0.0 ,
								x , y , z , 1.0 
								);							;
		HRESULT hr = D3DSprite_->DrawTransform( texture->texture_ , NULL , &d3dxMatrix , (D3DCOLOR)0xffffffff );
		DXASSERT( hr );
	}
	void D3DDevice::clear(){
		DXASSERT( D3DDevice8_->Clear( 0 , NULL , D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER , D3DCOLOR_XRGB( 0 , 0 , 0 ) , 1.0 , 0 ) );
	}
};