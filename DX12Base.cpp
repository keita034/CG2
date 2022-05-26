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
	//デスクリプタヒープの設定
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;//レンダーターゲットビュー
	rtvHeapDesc.NumDescriptors = swapChainDesc.BufferCount;//表裏の2つ
	//デスクリプタヒープの生成
	device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&rtvHeap));

	//バックバッファ
	backBuffers.resize(swapChainDesc.BufferCount);

	//スワップチェーンのバッファを処理
	for (size_t i = 0; i < backBuffers.size(); i++)
	{
		//バッファを取得
		swapChain->GetBuffer((UINT)i, IID_PPV_ARGS(&backBuffers[i]));
		//ヒープのハンドルの所得
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = rtvHeap->GetCPUDescriptorHandleForHeapStart();
		//裏か表かでアドレスがずれる
		rtvHandle.ptr += i * device->GetDescriptorHandleIncrementSize(rtvHeapDesc.Type);
		//ターゲットビューの設定
		D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
		//計算結果をSRGBに変換
		rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
		//ターゲットビューの生成
		device->CreateRenderTargetView(backBuffers[i], &rtvDesc, rtvHandle);
	}

	return S_OK;
}

HRESULT DX12Base::CreateSwapChain()
{
	swapChainDesc.Width = win->GetWindowSize().window_widht;//横幅
	swapChainDesc.Height = win->GetWindowSize().window_height;//縦幅
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;//色情報の書式
	swapChainDesc.SampleDesc.Count = 1;//マルチサンプルなし
	swapChainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER;//バックバッファ用
	swapChainDesc.BufferCount = 2;//バッファ数2
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;//フリップ後は破棄
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	//生成
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
	//対応レベルの配列
	D3D_FEATURE_LEVEL levels[] =
	{
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
	};

	//DXGIファクトリー
	result = CreateDXGIFactory(IID_PPV_ARGS(&dxgiFactory));
	if (FAILED(result))
	{
		return result;
	}

	//アダプター列挙用
	vector<IDXGIAdapter4*> adapters;
	//ここに特定の名前を持つアダプターオブジェクトが入る
	IDXGIAdapter4* tmpAdapter = nullptr;

	//パフォーマンスが高いのもから全て列挙
	for (UINT i = 0; dxgiFactory->EnumAdapterByGpuPreference(i, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&tmpAdapter)) != DXGI_ERROR_NOT_FOUND; i++)
	{
		adapters.push_back(tmpAdapter);
	}

	//Direct3Dデバイスの初期化
	D3D_FEATURE_LEVEL featureLevel;
	for (auto lv : levels)
	{
		if (D3D12CreateDevice(tmpAdapter, lv, IID_PPV_ARGS(&device)) == S_OK)
		{
			//生成可能なバージョンが見つかったらループを打ち切り
			featureLevel = lv;
			break;
		}
	}

	return result;
}

HRESULT DX12Base::InitializeCommand()
{
	//コマンドアロケータを生成
	result = device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&cmdAllocator));
	if (FAILED(result))
	{
		return result;
	}

	//コマンドリストを生成
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

	//コマンドキューの設定＆生成
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
	//フェンスの生成
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

	//DirectX12関連初期化
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
	//5元に戻す
	barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;//描画状態から
	barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;//表示状態へ
	commandList->ResourceBarrier(1, &barrierDesc);

	ExecuteCommand();

}

void DX12Base::ExecuteCommand()
{
	//命令のクローズ
	result = commandList->Close();
	assert(SUCCEEDED(result));
	//コマンドリストの実行
	ID3D12CommandList* commandListts[] = { commandList };
	commandQueue->ExecuteCommandLists(1, commandListts);

	//フリップ
	result = swapChain->Present(1, 0);
	assert(SUCCEEDED(result));

	//コマンド実行完了を待つ
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

	//キューをクリア
	result = cmdAllocator->Reset();
	assert(SUCCEEDED(result));
	//コマンドリストを貯める準備
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
	//1バックバッファ番号を取得
	UINT bbIndex = swapChain->GetCurrentBackBufferIndex();
	//書き込み可能に変更
	
	barrierDesc.Transition.pResource = backBuffers[bbIndex];//バックバッファを指定
	barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;//表示状態から
	barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;//描画状態へ
	commandList->ResourceBarrier(1, &barrierDesc);

	//2描画先変更
	rtvHandle = rtvHeap->GetCPUDescriptorHandleForHeapStart();
	rtvHandle.ptr += (bbIndex) * device->GetDescriptorHandleIncrementSize(rtvHeapDesc.Type);
	commandList->OMSetRenderTargets(1, &rtvHandle, false, nullptr);

	//3画面クリア
	FLOAT clearColor[] = { 0.1f, 0.25f, 0.5f, 0.0f };

	commandList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
}
