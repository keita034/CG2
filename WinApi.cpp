#include "WinApi.h"
#include<string>

WinApi* WinApi:: WinApi_ = NULL;
HWND WinApi::hwnd = nullptr;
WNDCLASSEX WinApi::WndClass = {};

//ウィンドウプロシージャ
LRESULT WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
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

void WinApi::CreateGameWindow(const wchar_t* title, UINT windowStyle, int32_t Width, int32_t Height)
{
	HINSTANCE hinst = GetModuleHandle(nullptr);
	//ウィンドウクラス生成＆登録
	WndClass.cbSize = sizeof(WNDCLASSEX);
	WndClass.lpfnWndProc = (WNDPROC)WindowProcedure;//コールバック関数の指定
	WndClass.lpszClassName = L"DirectXGame";//アプリケーションクラス名
	WndClass.hInstance = GetModuleHandle(nullptr);//ハンドルの取得
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);//カーソル設定

	RegisterClassEx(&WndClass);//アプリケーションクラス(ウィンドウの指定をOSに伝える)

	RECT wrc = { 0,0,Width,Height };//ウィンドウサイズを決める
	AdjustWindowRect(&wrc, windowStyle, false);//ウィンドウのサイズはちょっと面倒なので関数を使って補正する

	//ウィンドウオブジェクトの生成
	hwnd = CreateWindow(WndClass.lpszClassName,//クラス名指定
		title,//タイトルバーの文字
		windowStyle,//タイトルバーと境界線があるウィンドウです
		CW_USEDEFAULT,//表示X座標はOSにお任せします
		CW_USEDEFAULT,//表示Y座標はOSにお任せします
		wrc.right - wrc.left,//ウィンドウ幅
		wrc.bottom - wrc.top,//ウィンドウ高
		nullptr,//親ウィンドウハンドル
		nullptr,//メニューハンドル
		WndClass.hInstance,//呼び出しアプリケーションハンドル
		nullptr);//追加パラメータ

	ShowWindow(hwnd, SW_SHOW);//ウィンドウ表示
}

WinApi* WinApi:: GetInstance()
{
	if (!WinApi_)
	{
		WinApi_ = new WinApi;
	}

	return WinApi_;

}

void WinApi::Create()
{
	if (!WinApi_)
	{
		WinApi_ = new WinApi;
	}
}

void WinApi::Destroy()
{
	//クラス使用しないため登録解除
	UnregisterClass(GetWndclassex().lpszClassName, GetWndclassex().hInstance);

	delete WinApi_;
	WinApi_ = nullptr;
}

HWND WinApi::GetHwnd()
{
	return hwnd;
}

WNDCLASSEX WinApi::GetWndclassex()
{
	return WndClass;
}