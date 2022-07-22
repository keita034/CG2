#pragma once
#include"ErrorException.h"
#include"DirectX12Core.h"
#include"Model.h"

class ModelCreate
{
private:

	static ModelShareVaria modelShareVaria;

public:
	static Model* CreateModel(ModelShape shape, const wchar_t* filePath, bool smoothing = false);
	static Model* CreateModel(const char* filePath, bool smoothing = false);

private:
	//パイプラインの生成
	static void CreatPipeline();
	//デスクプリタヒープの生成
	static void CreateDescriptorHeap();
	//デスクプリタレンジの生成
	static void CreateDescriptorRange();
};

