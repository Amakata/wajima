/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/include/lib/Attic/Window.h,v 1.1 2002/05/10 19:17:09 ama Exp $
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
			init();
		}
		virtual void init(){
			_hWnd = CreateWindow( _className , _windowName , WS_OVERLAPPEDWINDOW , 
								CW_USEDEFAULT , 0 ,
								CW_USEDEFAULT , 0 ,
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