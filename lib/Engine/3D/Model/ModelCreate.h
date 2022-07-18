#pragma once
#include"ErrorException.h"
#include"DirectX12Core.h"
#include"Model.h"

class ModelCreate
{
private:

	static ModelShareVaria modelShareVaria;

	static Microsoft::WRL::ComPtr<ID3D12PipelineState> objPipelineState;
	static Microsoft::WRL::ComPtr<ID3D12RootSignature> objRootSignature;

public:
	static Model* CreateModel(ModelShape shape, const wchar_t* filePath);
	static Model* CreateModel(const char* filePath);

private:
	//パイプラインの生成
	static void CreatPipeline();
	static void CreatObjPipeline();
	//デスクプリタヒープの生成
	static void CreateDescriptorHeap();
	//デスクプリタレンジの生成
	static void CreateDescriptorRange();
};

