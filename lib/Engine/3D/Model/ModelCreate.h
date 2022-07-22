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
	//�p�C�v���C���̐���
	static void CreatPipeline();
	//�f�X�N�v���^�q�[�v�̐���
	static void CreateDescriptorHeap();
	//�f�X�N�v���^�����W�̐���
	static void CreateDescriptorRange();
};

