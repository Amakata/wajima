/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/test/lib/Window.h,v 1.1 2002/11/04 16:28:40 ama Exp $
 */

#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <windows.h>

namespace zefiro_stdtest{
	class Window
	{
	public:
		Window( HINSTANCE hInstance , LPTSTR className , LPTSTR windowName )
			:_hInstance(hInstance),_className(className),_windowName(windowName){
			init( 800 , 600 );
		}
		virtual void init( int width , int height ){
			_hWnd = CreateWindow( _className , _windowName , WS_OVERLAPPEDWINDOW , 
								CW_USEDEFAULT , 0 ,
								width , height ,
								NULL ,
								NULL ,
								_hInstance ,
								NULL
								);
		}
		virtual void show( int nCmdShow ){
			ShowWindow( _hWnd , nCmdShow );
		}

	protected:
		HWND		_hWnd;
		HINSTANCE	_hInstance;
		LPTSTR		_className;
		LPTSTR		_windowName;
	};
};

#endif //__WINDOW_H__