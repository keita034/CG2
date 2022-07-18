#pragma once
#include"Sprite.h"
#include"MyMath.h"
#include"DirectX12Core.h"

class SpriteCreat
{
private:

	static ModelShareVaria modelShareVaria;

public:
	static Sprite* CreateSprite(const wchar_t* filePath, bool flag3d);

private:
	//パイプラインの生成
	static void CreatPipeline();
	//デスクプリタヒープの生成
	static void CreateDescriptorHeap();
	//デスクプリタレンジの生成
	static void CreateDescriptorRange();
};

