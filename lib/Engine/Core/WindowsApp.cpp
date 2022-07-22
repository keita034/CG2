#include "WindowsApp.h"
#include"DirectX12Core.h"

//�E�C���h�E�v���V�[�W��
LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	//���b�Z�[�W�ɉ����ăQ�[���ŗL�̏������s��
	switch (msg) {
		//�E�C���h�E���j�����ꂽ
	case WM_DESTROY:
		//OS�ɑ΂��āA�A�v���̏I����`����
		PostQuitMessage(0);
		return 0;
	}

	//�W���̃��b�Z�[�W�������s��
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

WindowsApp* WindowsApp::GetInstance()
{
	//�V���O���g��
	static	WindowsApp windowsApp_;
	return &windowsApp_;
}

void WindowsApp::CreatWindow(const wchar_t* title,int width, int height)
{
	windowHeight = height;
	windowWidth = width;

	//�E�C���h�E�N���X�̐ݒ�
	wndclassex.cbSize = sizeof(WNDCLASSEX);
	wndclassex.lpfnWndProc = (WNDPROC)WindowProc;//�E�C���h�E�v���V�[�W����ݒ�
	wndclassex.lpszClassName = title;//�E�C���h�E�N���X��
	wndclassex.hInstance = GetModuleHandle(nullptr);//�E�C���h�E�n���h��
	wndclassex.hCursor = LoadCursor(NULL, IDC_ARROW);//�J�[�\���w��
	//�E�C���h�E�N���X��OS�ɓo�^����
	RegisterClassEx(&wndclassex);

	//�E�C���h�E�T�C�Y{X���W�@Y���W �����@�c��}
	RECT wrc = { 0,0,this->windowWidth,this->windowHeight };
	//�����ŃT�C�Y��␳����
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	//�E�C���h�E�I�u�W�F�N�g�̐���
	hwnd = CreateWindow(wndclassex.lpszClassName,//�N���X��
		title,				//�^�C�g���o�[�̕���
		WS_OVERLAPPEDWINDOW,		//�W���I�ȃE�C���h�E�X�^�C��
		CW_USEDEFAULT,				//�\��X���W(OS�ɔC����)
		CW_USEDEFAULT,				//�\��Y���W(OS�ɔC����)
		wrc.right - wrc.left,		//�E�C���h�E����
		wrc.bottom - wrc.top,		//�E�C���h�E�c��
		nullptr,					//�e�E�C���h�E�n���h��
		nullptr,					//���j���[�n���h��
		wndclassex.hInstance,				//�Ăяo���A�v���P�[�V�����n���h��
		nullptr);					//�I�v�V����

	//�E�C���h�E��\����Ԃɂ���
	ShowWindow(hwnd, SW_SHOW);

}

bool WindowsApp::MessageWindow()
{
	//���b�Z�[�W������H
	if (PeekMessage(&massege, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&massege); //�L�[���̓��b�Z�[�W�̏���
		DispatchMessage(&massege); //�v���V�[�W���Ƀ��b�Z�[�W�𑗂�
	}

	//�~�{�^���ŏI�����b�Z�[�W��������Q�[�����[�v�𔲂���
	if (massege.message == WM_QUIT)
	{
		//DirectX12Core::GetInstance()->GetDevice()->Re
		return false;
	}
	return true;
}

void WindowsApp::Break()
{
	//�E�C���h�E�N���X��o�^����
	UnregisterClass(wndclassex.lpszClassName, wndclassex.hInstance);
}

WNDCLASSEX WindowsApp::GetW()
{
	return wndclassex;
}

void WindowsApp::SetW(WNDCLASSEX W)
{
	wndclassex = W;
}

void WindowsApp::SetHwnd(HWND Hwnd)
{
	hwnd = Hwnd;
}

HWND WindowsApp::GetHwnd()
{
	return hwnd;
}

int WindowsApp::GetWindowHeight()
{
	return windowHeight;
}

int WindowsApp::GetWindowWidth()
{
	return windowWidth;
}