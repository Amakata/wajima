/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/main/include/test/Attic/WindowClass.h,v 1.3 2002/04/28 13:24:24 ama Exp $
 */

#ifndef __WINDOWCLASS_H__
#define __WINDOWCLASS_H__

#include <windows.h>

namespace zefiro_stdtest{
	
class WindowClass
{
public:
	WindowClass( HINSTANCE hInstance , WNDPROC wndProc , LPTSTR name )
		:_hInstance( hInstance ) , _lpszAppName(name){
		init( wndProc );
	}
	virtual void init( WNDPROC wndProc ){
		_wcex.cbSize		= sizeof( WNDCLASSEX );
		_wcex.style			= CS_HREDRAW | CS_VREDRAW;
		_wcex.lpfnWndProc	= (WNDPROC)wndProc;
		_wcex.cbClsExtra	= 0;
		_wcex.cbWndExtra	= 0;
		_wcex.hInstance		= _hInstance;
		_wcex.hIcon			= LoadIcon( _hInstance , IDI_APPLICATION );
		_wcex.hIconSm		= LoadIcon( _hInstance , IDI_APPLICATION );
		_wcex.hCursor		= LoadCursor( _hInstance , IDC_ARROW );
		_wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
		_wcex.lpszMenuName	= _lpszAppName;
		_wcex.lpszClassName	= _lpszAppName;
	}
	void setWindowClassName( LPTSTR name ){
		_lpszAppName = name;
	}
	virtual void registerClass(){
		RegisterClassEx( &_wcex );
	}
	virtual void unregisterClass(){
		UnregisterClass( _lpszAppName , _hInstance );
	}
protected:
	WNDCLASSEX	_wcex;
	LPTSTR		_lpszAppName;
	HINSTANCE	_hInstance;
};

};

#endif //__WINDOWCLASS_H__