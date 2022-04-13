#include<Windows.h>
#include<d3d12.h>
#include<dxgi1_6.h>
#include<cassert>
#include<vector>
#include<string>

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")

using namespace std;

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

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
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

#pragma region DirectX������

#ifdef _DEBUG
	ID3D12Debug* debugController;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
	{
		debugController->EnableDebugLayer();
	}
#endif // DEBUG

	HRESULT result;
	ID3D12Device* device = nullptr;
	IDXGIFactory7* dxgiFactory = nullptr;
	IDXGISwapChain4* swapChain = nullptr;
	ID3D12CommandAllocator* cmdAllocator = nullptr;
	ID3D12GraphicsCommandList* cmmandList = nullptr;
	ID3D12CommandQueue* cmmandQueue = nullptr;
	ID3D12DescriptorHeap* rtvHeap = nullptr;

	//DXGI�t�@�N�g���[
	result = CreateDXGIFactory(IID_PPV_ARGS(&dxgiFactory));
	assert(SUCCEEDED(result));

	//�A�_�v�^�[�񋓗p
	vector<IDXGIAdapter4*> adapters;
	//�����ɓ���̖��O�����A�_�v�^�[�I�u�W�F�N�g������
	IDXGIAdapter4* tmpAdapter = nullptr;

	//�p�t�H�[�}���X�������̂�����S�ė�
	for (UINT i = 0; dxgiFactory->EnumAdapterByGpuPreference(i,DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE,IID_PPV_ARGS(&tmpAdapter)) != DXGI_ERROR_NOT_FOUND; i++)
	{
		adapters.push_back(tmpAdapter);
	}

	//�Ή����x���̔z��
	D3D_FEATURE_LEVEL levels[] =
	{
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
	};

	//Direct3D�f�o�C�X�̏�����
	D3D_FEATURE_LEVEL featureLevel;
	for (auto lv: levels)
	{
		if (D3D12CreateDevice(tmpAdapter,lv,IID_PPV_ARGS(&device)) == S_OK)
		{
			//�����\�ȃo�[�W���������������烋�[�v��ł��؂�
			featureLevel = lv;
			break;
		}
	}

	//�R�}���h�A���P�[�^�𐶐�
	result = device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT,IID_PPV_ARGS(&cmdAllocator));
	assert(SUCCEEDED(result));

	//�R�}���h���X�g�𐶐�
	result = device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, cmdAllocator, nullptr, IID_PPV_ARGS(&cmmandList));
	assert(SUCCEEDED(result));

	//�R�}���h�L���[�̐ݒ聕����
	D3D12_COMMAND_QUEUE_DESC cmmandQueueDesc{};
	result = device->CreateCommandQueue(&cmmandQueueDesc, IID_PPV_ARGS(&cmmandQueue));
	assert(SUCCEEDED(result));

	//�X���b�v�`�F�[���̐ݒ�
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};
	swapChainDesc.Width = window_widht;//����
	swapChainDesc.Height = window_height;//�c��
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;//�F���̏���
	swapChainDesc.SampleDesc.Count = 1;//�}���`�T���v���Ȃ�
	swapChainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER;//�o�b�N�o�b�t�@�p
	swapChainDesc.BufferCount = 2;//�o�b�t�@��2
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;//�t���b�v��͔j��
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	//����
	result = dxgiFactory->CreateSwapChainForHwnd(cmmandQueue, hwnd, &swapChainDesc, nullptr, nullptr, (IDXGISwapChain1**)&swapChain);
	assert(SUCCEEDED(result));
	
	//�f�X�N���v�^�q�[�v�̐ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc{};
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;//�����_�[�^�[�Q�b�g�r���[
	rtvHeapDesc.NumDescriptors = swapChainDesc.BufferCount;//�\����2��
	//�f�X�N���v�^�q�[�v�̐���
	device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&rtvHeap));

	//�o�b�N�o�b�t�@
	vector<ID3D12Resource*> backBuffers;
	backBuffers.resize(swapChainDesc.BufferCount);

	//�X���b�v�`�F�[���̃o�b�t�@������
	for (size_t i = 0; i < backBuffers.size(); i++)
	{
		//�o�b�t�@���擾
		swapChain->GetBuffer((UINT)i, IID_PPV_ARGS(&backBuffers[i]));
		//�q�[�v�̃n���h���̏���
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = rtvHeap->GetCPUDescriptorHandleForHeapStart();
		//�����\���ŃA�h���X�������
		rtvHandle.ptr += i * device->GetDescriptorHandleIncrementSize(rtvHeapDesc.Type);
		//�^�[�Q�b�g�r���[�̐ݒ�
		D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
		//�v�Z���ʂ�SRGB�ɕϊ�
		rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
		//�^�[�Q�b�g�r���[�̐���
		device->CreateRenderTargetView(backBuffers[i], &rtvDesc, rtvHandle);
	}

	//�t�F���X�̐���
	ID3D12Fence* fence = nullptr;
	UINT64 fenceVal = 0;
	result = device->CreateFence(fenceVal,D3D12_FENCE_FLAG_NONE,IID_PPV_ARGS(&fence));

#pragma endregion

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

#pragma region ���t���[������

		//1�o�b�N�o�b�t�@�ԍ����擾
		UINT bbIndex = swapChain->GetCurrentBackBufferIndex();
		//�������݉\�ɕύX
		D3D12_RESOURCE_BARRIER barrierDesc{};
		barrierDesc.Transition.pResource = backBuffers[bbIndex];//�o�b�N�o�b�t�@���w��
		barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;//�\����Ԃ���
		barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;//�`���Ԃ�
		cmmandList->ResourceBarrier(1, &barrierDesc);

		//2�`���ύX
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = rtvHeap->GetCPUDescriptorHandleForHeapStart();
		rtvHandle.ptr += static_cast<unsigned long long>(bbIndex) * device->GetDescriptorHandleIncrementSize(rtvHeapDesc.Type);
		cmmandList->OMSetRenderTargets(1,&rtvHandle,false,nullptr);

		//3��ʃN���A
		FLOAT clearColor[] = { 0.1f,0.25f,0.5f,0.0f };
		cmmandList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);

		//4�`��

		//5���ɖ߂�
		barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;//�`���Ԃ���
		barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;//�\����Ԃ�
		cmmandList->ResourceBarrier(1, &barrierDesc);

		//���߂̃N���[�Y
		result = cmmandList->Close();
		assert(SUCCEEDED(result));
		//�R�}���h���X�g�̎��s
		ID3D12CommandList* cmmandListts[] = { cmmandList };
		cmmandQueue->ExecuteCommandLists(1, cmmandListts);

		//�t���b�v
		result = swapChain->Present(1, 0);
		assert(SUCCEEDED(result));

		//�R�}���h���s������҂�
		cmmandQueue->Signal(fence, ++fenceVal);
		if (fence->GetCompletedValue() != fenceVal)
		{
			HANDLE event = CreateEvent(nullptr, false, false, nullptr);
			fence->SetEventOnCompletion(fenceVal,event);
			if (event != 0)
			{
				WaitForSingleObject(event, INFINITE);
				CloseHandle(event);
			}
		}

		//�L���[���N���A
		result = cmdAllocator->Reset();
		assert(SUCCEEDED(result));
		//�R�}���h���X�g�𒙂߂鏀��
		result = cmmandList->Reset(cmdAllocator, nullptr);
		assert(SUCCEEDED(result));

#pragma endregion

	}

	//�N���X�g�p���Ȃ����ߓo�^����
	UnregisterClass(w.lpszClassName,w.hInstance);

	return 0;
}