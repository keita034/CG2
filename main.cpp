#include<Windows.h>

//ウィンドウプロシージャ
LRESULT WincowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_DESTROY://ウィンドウが破棄

		PostQuitMessage(0);//OSに終了を伝える
		return 0;
	}

	//標準の処理を行う
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//ウィンドウサイズ
	const int window_widht = 1200;
	const int window_height = 720;

	//ウィンドウクラス生成
	WNDCLASSEX w{};
	w.cbSize = sizeof(WNDCLASSEX);
	w.lpfnWndProc = (WNDPROC)WincowProc;//ウィンドウプロシージャを設定
	w.lpszClassName = L"DirectXGame";//クラス名
	w.hInstance = GetModuleHandle(nullptr);//ハンドル
	w.hCursor = LoadCursor(NULL,IDC_ARROW);//カーソル設定

	//クラスを登録
	RegisterClassEx(&w);
	//X,Y座標,縦,横幅
	RECT wrc = { 0,0,window_widht,window_height };
	//サイズ補正
	AdjustWindowRect(&wrc,WS_OVERLAPPEDWINDOW,false);

	//ウィンドウオブジェクトの生成
	HWND hwnd = CreateWindow(
		w.lpszClassName,//クラス名指定
		L"DirectXGame",//タイトルバーの文字
		WS_OVERLAPPEDWINDOW,//タイトルバーと境界線があるウィンドウです
		CW_USEDEFAULT,//表示X座標はOSにお任せします
		CW_USEDEFAULT,//表示Y座標はOSにお任せします
		wrc.right - wrc.left,//ウィンドウ幅
		wrc.bottom - wrc.top,//ウィンドウ高
		nullptr,//親ウィンドウハンドル
		nullptr,//メニューハンドル
		w.hInstance,//呼び出しアプリケーションハンドル
		nullptr);//追加パラメータ

	ShowWindow(hwnd, SW_SHOW);//ウィンドウ表示

	MSG msg{};

	//初期化処理

	while (true)
	{
		
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

		}

		//もうアプリケーションが終わるって時にmessageがWM_QUITになる
		if (msg.message == WM_QUIT)
		{
			break;
		}

		//毎フレーム更新
	}

	//クラス使用しないため登録解除
	UnregisterClass(w.lpszClassName,w.hInstance);

	return 0;
}