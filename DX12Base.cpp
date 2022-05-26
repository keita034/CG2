#include "DX12Base.h"
#include"WinApi.h"
#include<cassert>

WinApi* win = win->GetInstance();

using namespace std;

DX12Base* DX12Base::GetInstance()
{

	static DX12Base DXBase;

	return &DXBase;
}

HRESULT DX12Base::CreatFinalRenderTarget()
{
	//�f�X�N���v�^�q�[�v�̐ݒ�
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;//�����_�[�^�[�Q�b�g�r���[
	rtvHeapDesc.NumDescriptors = swapChainDesc.BufferCount;//�\����2��
	//�f�X�N���v�^�q�[�v�̐���
	device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&rtvHeap));

	//�o�b�N�o�b�t�@
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

	return S_OK;
}

HRESULT DX12Base::CreateSwapChain()
{
	swapChainDesc.Width = win->GetWindowSize().window_widht;//����
	swapChainDesc.Height = win->GetWindowSize().window_height;//�c��
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;//�F���̏���
	swapChainDesc.SampleDesc.Count = 1;//�}���`�T���v���Ȃ�
	swapChainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER;//�o�b�N�o�b�t�@�p
	swapChainDesc.BufferCount = 2;//�o�b�t�@��2
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;//�t���b�v��͔j��
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	//����
	if (commandQueue != 0)
	{
		result = dxgiFactory->CreateSwapChainForHwnd(commandQueue, win->GetHwnd(), &swapChainDesc, nullptr, nullptr, (IDXGISwapChain1**)&swapChain);
		if (FAILED(result))
		{
			return result;
		}
	}
	else
	{
		assert(SUCCEEDED(0));
	}

	return result;
}

HRESULT DX12Base::InitializeDXGIDevice()
{
	//�Ή����x���̔z��
	D3D_FEATURE_LEVEL levels[] =
	{
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
	};

	//DXGI�t�@�N�g���[
	result = CreateDXGIFactory(IID_PPV_ARGS(&dxgiFactory));
	if (FAILED(result))
	{
		return result;
	}

	//�A�_�v�^�[�񋓗p
	vector<IDXGIAdapter4*> adapters;
	//�����ɓ���̖��O�����A�_�v�^�[�I�u�W�F�N�g������
	IDXGIAdapter4* tmpAdapter = nullptr;

	//�p�t�H�[�}���X�������̂�����S�ė�
	for (UINT i = 0; dxgiFactory->EnumAdapterByGpuPreference(i, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&tmpAdapter)) != DXGI_ERROR_NOT_FOUND; i++)
	{
		adapters.push_back(tmpAdapter);
	}

	//Direct3D�f�o�C�X�̏�����
	D3D_FEATURE_LEVEL featureLevel;
	for (auto lv : levels)
	{
		if (D3D12CreateDevice(tmpAdapter, lv, IID_PPV_ARGS(&device)) == S_OK)
		{
			//�����\�ȃo�[�W���������������烋�[�v��ł��؂�
			featureLevel = lv;
			break;
		}
	}

	return result;
}

HRESULT DX12Base::InitializeCommand()
{
	//�R�}���h�A���P�[�^�𐶐�
	result = device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&cmdAllocator));
	if (FAILED(result))
	{
		return result;
	}

	//�R�}���h���X�g�𐶐�
	if (cmdAllocator != 0)
	{
		result = device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, cmdAllocator, nullptr, IID_PPV_ARGS(&commandList));
		if (FAILED(result))
		{
			return result;
		}
	}
	else
	{
		assert(SUCCEEDED(0));
	}

	//�R�}���h�L���[�̐ݒ聕����
	D3D12_COMMAND_QUEUE_DESC commandQueueDesc{};
	result = device->CreateCommandQueue(&commandQueueDesc, IID_PPV_ARGS(&commandQueue));
	if (FAILED(result))
	{
		return result;
	}

	return result;
}

HRESULT DX12Base::CreateFence()
{
	//�t�F���X�̐���
	result = device->CreateFence(fenceVal, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));

	return result;
}

void DX12Base::EnableDebugLayer()
{
	ID3D12Debug* debugController;

	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
	{
		debugController->EnableDebugLayer();
	}
}


DX12Base::DX12Base()
{
#ifdef _DEBUG
	EnableDebugLayer();
#endif

	//DirectX12�֘A������
	if (FAILED(InitializeDXGIDevice()))
	{
		assert(0);
		return;
	}
	if (FAILED(InitializeCommand()))
	{
		assert(0);
		return;
	}
	if (FAILED(CreateSwapChain()))
	{
		assert(0);
		return;
	}
	if (FAILED(CreatFinalRenderTarget()))
	{
		assert(0);
		return;
	}
	if (FAILED(CreateFence()))
	{
		assert(0);
		return;
	}
}

DX12Base::~DX12Base()
{
}

void DX12Base::EndDraw()
{
	//5���ɖ߂�
	barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;//�`���Ԃ���
	barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;//�\����Ԃ�
	commandList->ResourceBarrier(1, &barrierDesc);

	ExecuteCommand();

}

void DX12Base::ExecuteCommand()
{
	//���߂̃N���[�Y
	result = commandList->Close();
	assert(SUCCEEDED(result));
	//�R�}���h���X�g�̎��s
	ID3D12CommandList* commandListts[] = { commandList };
	commandQueue->ExecuteCommandLists(1, commandListts);

	//�t���b�v
	result = swapChain->Present(1, 0);
	assert(SUCCEEDED(result));

	//�R�}���h���s������҂�
	commandQueue->Signal(fence, ++fenceVal);
	if (fence->GetCompletedValue() != fenceVal)
	{
		HANDLE event = CreateEvent(nullptr, false, false, nullptr);
		fence->SetEventOnCompletion(fenceVal, event);
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
	if (commandList != 0)
	{
		result = commandList->Reset(cmdAllocator, nullptr);
		assert(SUCCEEDED(result));
	}
	else
	{
		assert(SUCCEEDED(0));
	}
}

void DX12Base::BeginDraw()
{
	//1�o�b�N�o�b�t�@�ԍ����擾
	UINT bbIndex = swapChain->GetCurrentBackBufferIndex();
	//�������݉\�ɕύX
	
	barrierDesc.Transition.pResource = backBuffers[bbIndex];//�o�b�N�o�b�t�@���w��
	barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;//�\����Ԃ���
	barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;//�`���Ԃ�
	commandList->ResourceBarrier(1, &barrierDesc);

	//2�`���ύX
	rtvHandle = rtvHeap->GetCPUDescriptorHandleForHeapStart();
	rtvHandle.ptr += (bbIndex) * device->GetDescriptorHandleIncrementSize(rtvHeapDesc.Type);
	commandList->OMSetRenderTargets(1, &rtvHandle, false, nullptr);

	//3��ʃN���A
	FLOAT clearColor[] = { 0.1f, 0.25f, 0.5f, 0.0f };

	commandList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
}
