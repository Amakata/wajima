#pragma once

#include "vertex.h"
#include "texture.h"

#define DXERROR_LOG( hr )	{	HRESULT hr2 = hr; if( hr2 != D3D_OK ){std::ofstream ofs;	ofs.open("error_log",std::ios_base::out | std::ios_base::app ); ofs <<__FILE__<<":"<<__LINE__<<":"<<hr2<< std::endl; ofs.close();}  }


class VertexBuffer {
public:
	VertexBuffer( LPDIRECT3DDEVICE8 device , int spriteSize ):vb_(NULL),cv_(NULL),spriteSize_(spriteSize){
		DXERROR_LOG(device->CreateVertexBuffer( sizeof(CUSTOMVERTEX) * spriteSize * 6 , 0 , D3DFVF_CUSTOMVERTEX , D3DPOOL_MANAGED , &vb_ ));
	}
	void lock(){
		if( vb_ != NULL && cv_ == NULL ){
			HRESULT hr;
			hr = vb_->Lock( 0 , 0 , (BYTE**)&cv_ , D3DLOCK_DISCARD );
			DXERROR_LOG(hr);
			if( D3D_OK != hr ){
				hr = vb_->Lock( 0 , 0 , (BYTE**)&cv_ , 0 );
				DXERROR_LOG(hr);
			}
		}
	}
	void unlock(){
		if( vb_ != NULL && cv_ != NULL ){
			DXERROR_LOG((vb_->Unlock()));
			cv_ = NULL;
		}
	}
	void setVertex( int numOfSprite , Texture *texture , float x , float y , float z  ){
		if( cv_ != NULL ){
			memcpy( &cv_[numOfSprite*6] , texture->getVertex() , sizeof CUSTOMVERTEX * 6 );
			for( int i=0 ; i<6 ; ++i ){
				cv_[numOfSprite*6+i].x += x;
				cv_[numOfSprite*6+i].y += y;
				cv_[numOfSprite*6+i].z += z;
			}
		}
	}
	virtual ~VertexBuffer(){
		if( vb_ != NULL ){
			vb_->Release();
		}
	}
	int getSpriteSize(){
		return spriteSize_;
	}
protected:
	friend class Device;
	LPDIRECT3DVERTEXBUFFER8 vb_;
	CUSTOMVERTEX*	cv_;
	int spriteSize_;
};