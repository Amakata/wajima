#pragma once

#include <dinput.h>

#include "KeyboardDevice.h"


class Input {
public:
	Input( HINSTANCE hinst ):dInput_(NULL){
		DirectInput8Create( hinst , DIRECTINPUT_VERSION , IID_IDirectInput8 , (void**)&dInput_ , NULL );
	}
	virtual ~Input(){
		if( dInput_ != NULL ){
			dInput_->Release();
		}
	}
	KeyboardDevice *createKeyboardDevice(){
		return new KeyboardDevice(dInput_);
	}
protected:
	LPDIRECTINPUT8	dInput_;
};