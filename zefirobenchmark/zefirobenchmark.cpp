// zefirobenchmark.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "zefirobenchmark.h"
#define MAX_LOADSTRING 100

// グローバル変数 :
HINSTANCE hInst;								// 現在のインターフェイス
TCHAR szTitle[MAX_LOADSTRING];					// タイトル バーのテキスト
TCHAR szWindowClass[MAX_LOADSTRING];			// メイン ウィンドウ クラス名

// このコード モジュールに含まれる関数の宣言を転送します :
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: ここにコードを挿入してください。
	MSG msg;
	HACCEL hAccelTable;

	// グローバル文字列を初期化しています。
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_ZEFIROBENCHMARK, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// アプリケーションの初期化を実行します。:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_ZEFIROBENCHMARK);

	// メイン メッセージ ループ :
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  関数 : MyRegisterClass()
//
//  目的 : ウィンドウ クラスを登録します。
//
//  コメント :
//
//    この関数および使い方は、'RegisterClassEx' 関数が追加された
//     Windows 95 より前の Win32 システムと互換させる場合にのみ必要です。
//    アプリケーションが、関連付けられた 
//    正しい形式の小さいアイコンを取得できるようにするには、
//    この関数を呼び出してください。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_ZEFIROBENCHMARK);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCTSTR)IDC_ZEFIROBENCHMARK;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

//
//   関数 : InitInstance(HANDLE, int)
//
//   目的 : インスタンス ハンドルを保存して、メイン ウィンドウを作成します。
//
//   コメント :
//
//        この関数で、グローバル変数でインスタンス ハンドルを保存し、
//        メイン プログラム ウィンドウを作成および表示します。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // グローバル変数にインスタンス処理を格納します。

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, 
		DISPLAY_WIDTH  + GetSystemMetrics(SM_CYFRAME)*2,
		DISPLAY_HEIGHT + GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYMENU) + GetSystemMetrics(SM_CYFRAME)*2 ,
		NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

class Application {
public:
	Application( HWND hWnd , bool windowed , bool transparent ):countOfTextureSize_(0),countOfTextureNumber_(0),transparent_(transparent){
		d3d_ = new D3D();
		device_ = d3d_->createDevice( hWnd , windowed );
		device_->setRenderState( transparent );
	}
	~Application(){
		delete device_;
		delete d3d_;
	}
	void render(){
		Texture *texture = device_->createTexture( getFilename(countOfTextureSize_) );
		VertexBuffer *buffer = device_->createVertexBuffer( getTextureNumber(countOfTextureNumber_) );
		DWORD now,old,begin;
		int frameCount = 0;
		float fps=0.0f;
		now = begin = timeGetTime();
		do{
			device_->render( buffer , texture );
			buffer->lock();
			for( int i=0 ; i<getTextureNumber(countOfTextureNumber_) ; ++i){
				buffer->setVertex( i , texture , (int)((float)rand()/RAND_MAX*DISPLAY_WIDTH) , (int)((float)rand()/RAND_MAX*DISPLAY_HEIGHT) , (float)rand()/RAND_MAX );
			}
			buffer->unlock();
			if( frameCount <= 0 ){
				old = now;
				now = timeGetTime();
				frameCount = 5;
				fps = 5.0f / (now - old) * 1000.0f;
			}
			frameCount--;
			std::ostringstream oss;
			oss << texture->getHeight() << "x" << texture->getWidth() << "x" << getTextureNumber(countOfTextureNumber_) <<"[Sprites] " << fps << "[fps] " << fps * texture->getHeight() * texture->getWidth() * getTextureNumber(countOfTextureNumber_) / 1000000.0f << "[Mtexel/s] " << fps * getTextureNumber(countOfTextureNumber_) * 2 << "[tri/s]";
			device_->renderFont(oss.str(),0,0,800,16);
			device_->present();
		}while( now - begin < 5000 );
		std::ofstream ofs;
		ofs.open("zefirobenchmarkoutput.txt",std::ios_base::out | std::ios_base::app );
		ofs << device_->toString() << " " << texture->getHeight() << "x" << texture->getWidth() << "x" << getTextureNumber(countOfTextureNumber_) <<" [Sprites] " << fps << " [fps] " << fps * texture->getHeight() * texture->getWidth() * getTextureNumber(countOfTextureNumber_) / 1000000.0f << " [Mtexel/s] " << fps * getTextureNumber(countOfTextureNumber_) * 2 << " [tri/s]" << std::endl; 
		ofs.close();		
		delete buffer;
		delete texture;
		++countOfTextureNumber_;
		if( countOfTextureNumber_ > 5 ){
			countOfTextureNumber_ = 0;
			++countOfTextureSize_;
		}
	}
	bool eof(){
		return (countOfTextureSize_ == 5 && countOfTextureNumber_ == 0);
	}
protected:
	int getTextureNumber( int countOfTextureSize ){
		if( transparent_ ){
			int numOfTexture[] = {100,250,500,1000,2000,4000};
			return numOfTexture[countOfTextureSize];
		}else{
			int numOfTexture[] = {1000,2500,5000,10000,20000,40000};
			return numOfTexture[countOfTextureSize];
		}
	}
	std::string getFilename( int countOfTextureSize ){
		if( transparent_ ){
			std::string texfile[5]={"16a.png","32a.png","64a.png","128a.png","256a.png"};
			return texfile[countOfTextureSize];
		}else{
			std::string texfile[5]={"16.png","32.png","64.png","128.png","256.png"};
			return texfile[countOfTextureSize];
		}
	}
	D3D *d3d_;
	Device *device_;
	int countOfTextureSize_;
	int countOfTextureNumber_;
	bool transparent_;
};


//
//  関数 : WndProc(HWND, unsigned, WORD, LONG)
//
//  目的 :  メイン ウィンドウのメッセージを処理します。
//
//  WM_COMMAND	- アプリケーション メニューの処理
//  WM_PAINT	- メイン ウィンドウの描画
//  WM_DESTROY	- 中止メッセージを表示して戻る
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	static Application *app;

	switch (message) 
	{
	case WM_RENDER:
		app->render();
		if( app->eof() ){
			delete app;
		}else{
			PostMessage( hWnd , WM_RENDER , 0 , 0 );
		}
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam); 
		wmEvent = HIWORD(wParam); 
		// 選択されたメニューの解析 :
		switch (wmId)
		{
		case IDM_FULLSCREEN:
			app = new Application( hWnd , false , false );
			PostMessage( hWnd , WM_RENDER , 0 , 0 );
			break;
		case IDM_WINDOW:
			app = new Application( hWnd , true , false);
			PostMessage( hWnd , WM_RENDER , 0 , 0 );
			break;
		case IDM_FULLSCREEN_ALPHA:
			app = new Application( hWnd , false , true );
			PostMessage( hWnd , WM_RENDER , 0 , 0 );
			break;
		case IDM_WINDOW_ALPHA:
			app = new Application( hWnd , true , true );
			PostMessage( hWnd , WM_RENDER , 0 , 0 );
			break;
		case IDM_ABOUT:
			DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: 描画コードをここに追加してください...
		EndPaint(hWnd, &ps);
		break;
	case WM_SIZE:
		SetWindowPos( 
			hWnd ,
			HWND_TOP ,
			0 ,
			0 ,
			DISPLAY_WIDTH + GetSystemMetrics(SM_CYFRAME)*2 ,
			DISPLAY_HEIGHT + GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYMENU) + GetSystemMetrics(SM_CYFRAME)*2 ,
			SWP_DRAWFRAME|SWP_NOMOVE|SWP_SHOWWINDOW 
		);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// バージョン情報ボックスのメッセージ ハンドラです。
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;
	}
	return FALSE;
}
