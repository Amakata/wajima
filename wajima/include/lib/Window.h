/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/include/lib/Attic/Window.h,v 1.2 2002/09/18 14:41:32 ama Exp $
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