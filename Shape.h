#pragma once
#include<DirectXMath.h>
#include <Windows.h>
#include <d3dcompiler.h>
#include<d3d12.h>

struct VertexPosColor
{
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT4 color;
};

//�u�����h���[�h
enum BlendMode
{
	AE_BLENDMODE_NOBLEND,//�m�[�u�����h�i�f�t�H���g�j
	AE_BLENDMODE_ALPHA,// ���u�����h
	AE_BLENDMODE_ADD,// ���Z�u�����h
	AE_BLENDMODE_SUB,// ���Z�u�����h
	AE_BLENDMODE_MULA,// ��Z�u�����h
	AE_BLENDMODE_INVSRC,// ���]�u�����h
};

//�p�C�v���C���X�e�[�g�E���[�g�V�O�l�`��
struct StateSignature
{
	// �p�C�v�����X�e�[�g
	ID3D12PipelineState* pipelineState;

	// ���[�g�V�O�l�`��
	ID3D12RootSignature* rootSignature;
};

class Shape
{
private:

	HRESULT ShaderInit();
	HRESULT CreatePipeline(D3D12_PRIMITIVE_TOPOLOGY_TYPE type, BlendMode Mode);


	//�O�p�`�`�搔
	uint32_t indexTriangle;



	HRESULT result;

	D3D12_INPUT_ELEMENT_DESC inputLayout[2];
};

