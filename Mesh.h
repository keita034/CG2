#pragma once
#include <d3d12.h>
#include<DirectXMath.h>

struct PosColr
{
	DirectX::XMFLOAT3 pos;//���W
	DirectX::XMFLOAT4 colr;//�J���[
};

struct PipelineSet
{
	//�p�C�v���C���X�e�[�g
	ID3D12PipelineState* pipelineState;
	//���[�g�V�O�l�`��
	ID3D12RootSignature* rootSignature;
};

struct Buff
{
	//���_�o�b�t�@
	ID3D12Resource* vertBuff;
	//���_�}�b�v
	PosColr* vertMap;
	//���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView;
	//�C���f�b�N�X�o�b�t�@�̐���
	ID3D12Resource* indexBuff;
	////�C���f�b�N�X�o�b�t�@���}�b�s���O
	uint16_t* indexMap;
	//�C���f�b�N�X�o�b�t�@�r���[�̍쐬
	D3D12_INDEX_BUFFER_VIEW ibView;
};

enum BlendMode
{
	BLENDMODE_NOBLEND,//�m�[�u�����h�i�f�t�H���g�j
	BLENDMODE_ALPHA,//���u�����h
	BLENDMODE_ADD,//���Z�u�����h
	BLENDMODE_SUB,//���Z�u�����h
	BLENDMODE_MULA,//��Z�u�����h
	BLENDMODE_INVSRC//���]�u�����h
};

class Mesh
{
public:
	void DrawTriangle(float x1,float y1, float x2, float y2, float x3, float y3, DirectX::XMFLOAT4 colr);
	void DrawTriangleUpdate();
	Mesh(DX12Base* base);
private:

	//���_�o�b�t�@
	ID3D12Resource* vertBuff;
	//���_�}�b�v
	PosColr* vertMap;
	//���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView;
	//�C���f�b�N�X�o�b�t�@�̐���
	ID3D12Resource* indexBuff;
	////�C���f�b�N�X�o�b�t�@���}�b�s���O
	uint16_t* indexMap;
	//�C���f�b�N�X�o�b�t�@�r���[�̍쐬
	D3D12_INDEX_BUFFER_VIEW ibView;

	//�p�C�v���C���X�e�[�g
	ID3D12PipelineState* pipelineState;
	//���[�g�V�O�l�`��
	ID3D12RootSignature* rootSignature;

	//�O�p�`�`����
	UINT maxCount = 2048;
	//�O�p�`���_��
	UINT VertexCount = 3;

	UINT count = 0;

	ID3D12Device* device = nullptr;

	ID3D12GraphicsCommandList* commandList = nullptr;

	void CreatPipeline();

	void CreateBuff();
};

