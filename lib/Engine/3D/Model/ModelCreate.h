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
	//�p�C�v���C���̐���
	static void CreatPipeline();
	static void CreatObjPipeline();
	//�f�X�N�v���^�q�[�v�̐���
	static void CreateDescriptorHeap();
	//�f�X�N�v���^�����W�̐���
	static void CreateDescriptorRange();
};

