#pragma once

#include <dinput.h>
#include "logger.h"

class KeyboardDevice
{
public:
	KeyboardDevice( LPDIRECTINPUT8 dinput ){
		DXIERROR_LOG(dinput->CreateDevice( GUID_SysKeyboard , &device_ , NULL ));
		DXIERROR_LOG(device_->SetDataFormat( &c_dfDIKeyboard ));
		DXIERROR_LOG(device_->Acquire());
	}
	virtual ~KeyboardDevice(){
		if( device_ != NULL ){
			DXIERROR_LOG(device_->Unacquire());
			device_->Release();
		}
	}
	bool getState(){
		HRESULT hr = device_->GetDeviceState(256,keyState_);
		DXIERROR_LOG(hr);
		if( DI_OK == hr ){
			return true;
		}else if( hr == DIERR_INPUTLOST ){
			DXIERROR_LOG(device_->Acquire());
			return false;
		}else{	
			return false;
		}
	}
	bool getKey( int keyValue ){
		if( keyState_[keyValue] & 0x80 ){
			return true;
		}
		else{
			return false;
		}
	}
protected:
	LPDIRECTINPUTDEVICE8 device_;
	BYTE keyState_[256];
};