#pragma once
#include<Windows.h>
#include <cstdint>
#include<string>

const std::wstring TitleName = L"DirectXGame";
//ウィンドウサイズ
const int window_widht = 1200;
const int window_height = 720;

class WinApi
{
public:

	/**
	* ゲーム用ウィンドウの生成
	* @param title ウィンドウタイトル
	* @param windowClass ウィンドウスタイル
	* * @param windowClass ウィンドウ横幅
	* * @param windowClass ウィンドウ縦幅
	*/
	void CreateGameWindow(const wchar_t* title = TitleName.data(), UINT windowStyle = WS_OVERLAPPEDWINDOW, int32_t Width = window_widht, int32_t Height = window_height);

	 HWND GetHwnd();

	WNDCLASSEX GetWndclassex();

	 WinApi* GetInstance();

	 void Create();

	 void Destroy();

private:

	static HWND hwnd;   // ウィンドウハンドル
	static WNDCLASSEX WndClass; // ウィンドウクラス
	UINT msg;
	WPARAM wparam;
	LPARAM lparam;

	static WinApi* WinApi_;

	// 隠し
	WinApi() = default;
	~WinApi() = default;
};

