#pragma once
#include<Windows.h>
#include<d3d12.h>
#include<vector>
#include<dxgi1_6.h>

class DX12Base
{
public:

	static DX12Base* GetInstance();

	//デバイスの取得
	ID3D12Device* GetDevice()
	{
		return device;
	}

	//描画コマンドリストの取得DX12Base->GetCommandList()
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

	//デスクリプタヒープの設定
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc{};

	//フェンスの生成
	UINT64 fenceVal = 0;

	//スワップチェーンの設定
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};

	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle;

	//最終的なレンダーターゲットの生成
	HRESULT CreatFinalRenderTarget();

	//スワップチェインの生成
	HRESULT CreateSwapChain();

	//DXGIまわり初期化
	HRESULT InitializeDXGIDevice();

	//コマンドまわり初期化
	HRESULT InitializeCommand();

	//フェンス生成
	HRESULT CreateFence();

	//デバッグレイヤーを有効にする
	void EnableDebugLayer();



	DX12Base();
	~DX12Base();
};

