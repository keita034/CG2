#include<Windows.h>

//�E�B���h�E�v���V�[�W��
LRESULT WincowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
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

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//�E�B���h�E�T�C�Y
	const int window_widht = 1200;
	const int window_height = 720;

	//�E�B���h�E�N���X����
	WNDCLASSEX w{};
	w.cbSize = sizeof(WNDCLASSEX);
	w.lpfnWndProc = (WNDPROC)WincowProc;//�E�B���h�E�v���V�[�W����ݒ�
	w.lpszClassName = L"DirectXGame";//�N���X��
	w.hInstance = GetModuleHandle(nullptr);//�n���h��
	w.hCursor = LoadCursor(NULL,IDC_ARROW);//�J�[�\���ݒ�

	//�N���X��o�^
	RegisterClassEx(&w);
	//X,Y���W,�c,����
	RECT wrc = { 0,0,window_widht,window_height };
	//�T�C�Y�␳
	AdjustWindowRect(&wrc,WS_OVERLAPPEDWINDOW,false);

	//�E�B���h�E�I�u�W�F�N�g�̐���
	HWND hwnd = CreateWindow(
		w.lpszClassName,//�N���X���w��
		L"DirectXGame",//�^�C�g���o�[�̕���
		WS_OVERLAPPEDWINDOW,//�^�C�g���o�[�Ƌ��E��������E�B���h�E�ł�
		CW_USEDEFAULT,//�\��X���W��OS�ɂ��C�����܂�
		CW_USEDEFAULT,//�\��Y���W��OS�ɂ��C�����܂�
		wrc.right - wrc.left,//�E�B���h�E��
		wrc.bottom - wrc.top,//�E�B���h�E��
		nullptr,//�e�E�B���h�E�n���h��
		nullptr,//���j���[�n���h��
		w.hInstance,//�Ăяo���A�v���P�[�V�����n���h��
		nullptr);//�ǉ��p�����[�^

	ShowWindow(hwnd, SW_SHOW);//�E�B���h�E�\��

	MSG msg{};

	//����������

	while (true)
	{
		
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

		}

		//�����A�v���P�[�V�������I�����Ď���message��WM_QUIT�ɂȂ�
		if (msg.message == WM_QUIT)
		{
			break;
		}

		//���t���[���X�V
	}

	//�N���X�g�p���Ȃ����ߓo�^����
	UnregisterClass(w.lpszClassName,w.hInstance);

	return 0;
}