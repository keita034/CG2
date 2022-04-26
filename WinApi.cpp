#include "WinApi.h"
#include<string>

WinApi* WinApi:: WinApi_ = NULL;
HWND WinApi::hwnd = nullptr;
WNDCLASSEX WinApi::WndClass = {};

//�E�B���h�E�v���V�[�W��
LRESULT WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_DESTROY://�E�B���h�E���j��

		PostQuitMessage(0);//OS�ɏI����`����
		return 0;
	}

	//�W���̏������s��
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

void WinApi::CreateGameWindow(const wchar_t* title, UINT windowStyle, int32_t Width, int32_t Height)
{
	HINSTANCE hinst = GetModuleHandle(nullptr);
	//�E�B���h�E�N���X�������o�^
	WndClass.cbSize = sizeof(WNDCLASSEX);
	WndClass.lpfnWndProc = (WNDPROC)WindowProcedure;//�R�[���o�b�N�֐��̎w��
	WndClass.lpszClassName = L"DirectXGame";//�A�v���P�[�V�����N���X��
	WndClass.hInstance = GetModuleHandle(nullptr);//�n���h���̎擾
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);//�J�[�\���ݒ�

	RegisterClassEx(&WndClass);//�A�v���P�[�V�����N���X(�E�B���h�E�̎w���OS�ɓ`����)

	RECT wrc = { 0,0,Width,Height };//�E�B���h�E�T�C�Y�����߂�
	AdjustWindowRect(&wrc, windowStyle, false);//�E�B���h�E�̃T�C�Y�͂�����Ɩʓ|�Ȃ̂Ŋ֐����g���ĕ␳����

	//�E�B���h�E�I�u�W�F�N�g�̐���
	hwnd = CreateWindow(WndClass.lpszClassName,//�N���X���w��
		title,//�^�C�g���o�[�̕���
		windowStyle,//�^�C�g���o�[�Ƌ��E��������E�B���h�E�ł�
		CW_USEDEFAULT,//�\��X���W��OS�ɂ��C�����܂�
		CW_USEDEFAULT,//�\��Y���W��OS�ɂ��C�����܂�
		wrc.right - wrc.left,//�E�B���h�E��
		wrc.bottom - wrc.top,//�E�B���h�E��
		nullptr,//�e�E�B���h�E�n���h��
		nullptr,//���j���[�n���h��
		WndClass.hInstance,//�Ăяo���A�v���P�[�V�����n���h��
		nullptr);//�ǉ��p�����[�^

	ShowWindow(hwnd, SW_SHOW);//�E�B���h�E�\��
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
	//�N���X�g�p���Ȃ����ߓo�^����
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