#pragma once

#include <string>
#include "vertex.h"

#define DXERROR_LOG( hr )	{	HRESULT hr2 = hr; if( hr2 != D3D_OK ){std::ofstream ofs;	ofs.open("error_log",std::ios_base::out | std::ios_base::app ); ofs <<__FILE__<<":"<<__LINE__<<":"<<hr2<< std::endl; ofs.close();} }

class Texture {
public:
	Texture( LPDIRECT3DDEVICE8 device , std::string filename ):texture_(NULL){
		HRESULT hr;
		D3DXIMAGE_INFO info;
		D3DSURFACE_DESC desc;
		hr = D3DXCreateTextureFromFileExA( device , // �e�N�X�`���[���쐬����f�o�C�X
											filename.c_str() , // �ǂݍ��ރt�@�C����
											D3DX_DEFAULT , // ��
											D3DX_DEFAULT , // ����
											1 , // �~�j�}�b�v���x��
											0 , // �����_�����O�^�[�Q�b�gOFF
											D3DFMT_A8R8G8B8, // �t�@�C������J���[�t�H�[�}�b�g������
											D3DPOOL_DEFAULT , // �v�[���̕���
											D3DX_FILTER_LINEAR , // �t�B���^�̕���
											D3DX_FILTER_LINEAR , // �t�B���^�̕���
											0 , // �J���[�L�[OFF
											&info , // �ǂݍ��񂾃C���[�W�̏��
											NULL , // �p���b�g���
											&texture_ // �e�N�X�`��
											);
		DXERROR_LOG(hr);
		width_ = info.Width;
		height_ = info.Height;
		DXERROR_LOG(texture_->GetLevelDesc( 0 , &desc ));
		memset( cv_ , 0 , sizeof CUSTOMVERTEX * 6 );
		float heightRatio = (info.Height + 0.5f )/ desc.Height;
		float widthRatio = (info.Width + 0.5f ) / desc.Width;;
														cv_[0].rhw = 1.0f;
		cv_[1].x = info.Width;	cv_[1].y = info.Height;	cv_[1].rhw = 1.0f;	cv_[1].tu = widthRatio;	cv_[1].tv = heightRatio;
								cv_[2].y = info.Height;	cv_[2].rhw = 1.0f;							cv_[2].tv = heightRatio;
		cv_[3].x = info.Width;							cv_[3].rhw = 1.0f;	cv_[3].tu = widthRatio;
		cv_[4] = cv_[1];
														cv_[5].rhw = 1.0f;

	}
	virtual ~Texture(){
		if( texture_ != NULL ){
			texture_->Release();
		}
	}
	CUSTOMVERTEX *getVertex(){
		return cv_;
	}
	int getWidth(){
		return width_;
	}
	int getHeight(){
		return height_;
	}
protected:
	friend class Device;
	LPDIRECT3DTEXTURE8 texture_;
	CUSTOMVERTEX cv_[6];
	int width_;
	int height_;
};