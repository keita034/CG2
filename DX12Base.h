#pragma once
#include<Windows.h>
#include<d3d12.h>
#include<vector>
#include<dxgi1_6.h>

class DX12Base
{
public:

	static DX12Base* GetInstance();

	//�f�o�C�X�̎擾
	ID3D12Device* GetDevice()
	{
		return device;
	}

	//�`��R�}���h���X�g�̎擾DX12Base->GetCommandList()
	ID3D12GraphicsCommandList* GetCommandList()
	{
		return commandList;
	}

	ID3D12DescriptorHeap* GetRtvHeap()
	{
		return rtvHeap;
	}

	IDXGISwapChain4* GetSwapChain()
	{
		return swapChain;
	}

	D3D12_CPU_DESCRIPTOR_HANDLE GetRtvHandle()
	{
		return rtvHandle;
	}

	ID3D12CommandAllocator* GetCmdAllocator()
	{
		return cmdAllocator;
	}

	ID3D12CommandQueue* GetCommandQueue()
	{
		return commandQueue;
	}

	D3D12_DESCRIPTOR_HEAP_DESC GetRtvHeapDesc()
	{
		return rtvHeapDesc;
	}

	IDXGIFactory6* GetDxgiFactory()
	{
		return dxgiFactory;
	}

	void BeginDraw();

	void EndDraw();

	void ExecuteCommand();

private:
	HRESULT result;
	ID3D12Device* device = nullptr;
	IDXGIFactory7* dxgiFactory = nullptr;
	IDXGISwapChain4* swapChain = nullptr;
	ID3D12CommandAllocator* cmdAllocator = nullptr;
	ID3D12GraphicsCommandList* commandList = nullptr;
	ID3D12CommandQueue* commandQueue = nullptr;
	ID3D12DescriptorHeap* rtvHeap = nullptr;

	ID3D12Fence* fence = nullptr;

	std::vector<ID3D12Resource*> backBuffers;
	
	D3D12_RESOURCE_BARRIER barrierDesc{};

	//�f�X�N���v�^�q�[�v�̐ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc{};

	//�t�F���X�̐���
	UINT64 fenceVal = 0;

	//�X���b�v�`�F�[���̐ݒ�
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};

	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle;

	//�ŏI�I�ȃ����_�[�^�[�Q�b�g�̐���
	HRESULT CreatFinalRenderTarget();

	//�X���b�v�`�F�C���̐���
	HRESULT CreateSwapChain();

	//DXGI�܂�菉����
	HRESULT InitializeDXGIDevice();

	//�R�}���h�܂�菉����
	HRESULT InitializeCommand();

	//�t�F���X����
	HRESULT CreateFence();

	//�f�o�b�O���C���[��L���ɂ���
	void EnableDebugLayer();



	DX12Base();
	~DX12Base();
};

