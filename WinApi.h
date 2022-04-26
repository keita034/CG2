#pragma once
#include<Windows.h>
#include <cstdint>
#include<string>

const std::wstring TitleName = L"DirectXGame";
//�E�B���h�E�T�C�Y
const int window_widht = 1200;
const int window_height = 720;

class WinApi
{
public:

	/**
	* �Q�[���p�E�B���h�E�̐���
	* @param title �E�B���h�E�^�C�g��
	* @param windowClass �E�B���h�E�X�^�C��
	* * @param windowClass �E�B���h�E����
	* * @param windowClass �E�B���h�E�c��
	*/
	void CreateGameWindow(const wchar_t* title = TitleName.data(), UINT windowStyle = WS_OVERLAPPEDWINDOW, int32_t Width = window_widht, int32_t Height = window_height);

	 HWND GetHwnd();

	WNDCLASSEX GetWndclassex();

	 WinApi* GetInstance();

	 void Create();

	 void Destroy();

private:

	static HWND hwnd;   // �E�B���h�E�n���h��
	static WNDCLASSEX WndClass; // �E�B���h�E�N���X
	UINT msg;
	WPARAM wparam;
	LPARAM lparam;

	static WinApi* WinApi_;

	// �B��
	WinApi() = default;
	~WinApi() = default;
};

