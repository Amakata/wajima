#pragma once

#include "vertex.h"
#include "texture.h"

class VertexBuffer {
public:
	VertexBuffer( LPDIRECT3DDEVICE8 device , int spriteSize ):vb_(NULL),cv_(NULL),spriteSize_(spriteSize){
		device->CreateVertexBuffer( sizeof(CUSTOMVERTEX) * spriteSize * 6 , 0 , D3DFVF_CUSTOMVERTEX , D3DPOOL_MANAGED , &vb_ );
	}
	void lock(){
		if( vb_ != NULL && cv_ == NULL ){
			vb_->Lock( 0 , 0 , (BYTE**)&cv_ , D3DLOCK_DISCARD );
		}
	}
	void unlock(){
		if( vb_ != NULL && cv_ != NULL ){
			vb_->Unlock();
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