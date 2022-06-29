#pragma once
//#DirectX�̂��
#include"ErrorException.h"

//����.h
#include "DirectX12Core.h"
#include"WindowsApp.h"
#include"MyMath.h"

//pragma comment
#pragma comment(lib, "d3dcompiler.lib")


//using namespace


//���W�E�J���[
struct PosColor
{
	MyMath::Vector3 pos;//���W
	MyMath::Vector4 color;//�J���[
};

//�p�C�v���C���E���[�g�V�O�l�`���Z�b�g
struct PipelineSet
{

	//�p�C�v���C���X�e�[�g
	Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState;
	//���[�g�V�O�l�`��
	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature;
};

//�o�b�t�@�֘A
struct Buff
{
	//���_�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource> vertBuff;
	//���_�}�b�v
	PosColor* vertMap;
	//���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	//�C���f�b�N�X�o�b�t�@�̐���
	Microsoft::WRL::ComPtr<ID3D12Resource> indexBuff;
	////�C���f�b�N�X�o�b�t�@���}�b�s���O
	uint16_t* indexMap;
	//�C���f�b�N�X�o�b�t�@�r���[�̍쐬
	D3D12_INDEX_BUFFER_VIEW ibView{};
};

//�u�����h���[�h
enum class BlendMode
{
	AX_BLENDMODE_NOBLEND,//�m�[�u�����h�i�f�t�H���g�j
	AX_BLENDMODE_ALPHA,//���u�����h
	AX_BLENDMODE_ADD,//���Z�u�����h
	AX_BLENDMODE_SUB,//���Z�u�����h
	AX_BLENDMODE_MULA,//��Z�u�����h
	AX_BLENDMODE_INVSRC,//���]�u�����h

	AX_BLENDMODE_MAX//�u�����h��ސ�
};

class Mesh
{
private:

	DirectX12Core* directX12Core = nullptr;

	//�萔�o�b�t�@��GPU���\�[�X�̃|�C���^
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffTransform = nullptr;
	//�萔�o�b�t�@�̃}�b�s���O�p�|�C���^
	ConstBufferDataTransform* constMapTransform = nullptr;

	//�u�����h���[�h
	UINT blendMode;
	char PADDING[4];

	//�O�p�`�`��p�C�v���C���Z�b�g
	std::array<std::unique_ptr<PipelineSet>, (size_t)BlendMode::AX_BLENDMODE_MAX>trianglePipelineSet;
	//���C���`��p�C�v���C���Z�b�g
	std::array<std::unique_ptr<PipelineSet>, (size_t)BlendMode::AX_BLENDMODE_MAX>linePipelineSet;

	//�O�p�`�o�b�t�@
	std::unique_ptr <Buff> triangleBuff;
	//�O�p�`�`����
	UINT triangleMaxCount = 4096;
	//�O�p�`���_��
	UINT triangleVertexCount = 3;
	//�O�p�`�C���f�b�N�X��
	UINT triangleIndexCount = 0;
	//�O�p�`�g�p��
	UINT triangleCount = 0;

	//���o�b�t�@
	std::unique_ptr <Buff> lineBuff;
	//���`����
	UINT lineMaxCount = 4096;
	//�����_��
	UINT lineVertexCount = 2;
	//���C���f�b�N�X��
	UINT lineIndexCount = 0;
	//���g�p��
	UINT lineCount = 0;

	//�l�p�`�o�b�t�@
	std::unique_ptr <Buff> boxBuff;
	//�l�p�`�`����
	UINT boxMaxCount = 2048;
	//�l�p�`���_��
	UINT boxVertexCount = 4;
	//�l�p�`�C���f�b�N�X��
	UINT boxIndexCount = 6;
	//�l�p�`�g�p��
	UINT boxCount = 0;

public:

	///<summary>
	///�O�p�`��`�悷��
	///</summary>
	///<param name="x1">: �`�悷��O�p�`�̒��_1 X</param>
	///<param name="y1">: �`�悷��O�p�`�̒��_1 Y</param>
	///<param name="x2">: �`�悷��O�p�`�̒��_2 X</param>
	///<param name="y2">: �`�悷��O�p�`�̒��_2 Y</param>
	///<param name="x3">: �`�悷��O�p�`�̒��_3 X</param>
	///<param name="y3">: �`�悷��O�p�`�̒��_3 Y</param>
	///<param name="color">: �`�悷��O�p�`�̐F</param>
	///<param name="fillFlag">: �O�p�`�̒��g��h��Ԃ����t���O</param>
	void DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, MyMath::Vector4 color, int fillFlag);

	///<summary>
	///����`�悷��
	///</summary>
	///<param name="x1">: �`�悷����̎n�_���W X</param>
	///<param name="y1">: �`�悷����̎n�_���W Y</param>
	///<param name="x2">: �`�悷����̏I�_���W X</param>
	///<param name="y2">: �`�悷����̏I�_���W Y</param>
	///<param name="color">: �`�悷����̐F</param>
	void DrawLine(float x1, float y1, float x2, float y2, MyMath::Vector4 color);

	///<summary>
	///�l�p�`��`�悷��
	///</summary>
	///<param name="x">: �`�悷��l�p�`�̒��S���W X</param>
	///<param name="y">: �`�悷��l�p�`�̒��S���W Y</param>
	///<param name="radiusX">: �`�悷��l�p�`�̔��a X</param>
	///<param name="radiusY">: �`�悷��l�p�`�̔��a Y</param>
	///<param name="angle">: �`�悷��l�p�`�̉�]�p(�ʓx�@)</param>
	///<param name="color">: �`�悷��l�p�`�̐F</param>
	///<param name="fillFlag">: �l�p�`�̒��g��h��Ԃ����t���O</param>
	void DrawBox(float x, float y, float radiusX, float radiusY, float angle, MyMath::Vector4 color, int fillFlag);

	///<summary>
	///�ȉ~��`�悷��
	///</summary>
	///<param name="x">�ȉ~�̒��S���W X</param>
	///<param name="y">�ȉ~�̒��S���W Y</param>
	///<param name="radiusX">�ȉ~�̔��a X</param>
	///<param name="radiusY">�ȉ~�̔��a Y</param>
	///<param name="angle">�ȉ~�̉�]�p(rad)</param>
	///<param name="color">�ȉ~�̐F</param>
	void DrawEllipse(float x, float y, float radiusX, float radiusY, float angle, MyMath::Vector4 color, int fillMode);

	///<summary>
	///�J�E���g������
	///</summary>
	void DrawReset();

	///<summary>
	///�u�����h���[�h��ݒ肷��
	///</summary>
	///<param name="mode">: �u�����h���[�h</param>
	void SetBlendMode(BlendMode mode);

	///<summary>
	///�F�R�[�h���擾����
	///</summary>
	///<param name="red">: �擾�������F�̋P�x�l : �����l255 (0�`255)</param>
	///<param name="blue">: �擾�������F�̋P�x�l : �����l255 (0�`255)</param>
	///<param name="green">: �擾�������F�̋P�x�l : �����l255 (0�`255)</param>
	///<param name="alpha">: �擾�������F�̓��ߗ� : �����l255 (0�`255)</param>
	///<returns>�F�R�[�h</returns>
	MyMath::Vector4 GetColor(int red = 255, int blue = 255, int green = 255, int alpha = 255);

	//�R���X�g���N�^
	Mesh();

private:

	//�O�p�`��`�悷��(���g�h��Ԃ�)
	void DrawTriangleFill(float x1, float y1, float x2, float y2, float x3, float y3, MyMath::Vector4 color);

	//�l�p�`��`�悷��(���g�h��Ԃ�)
	void DrawBoxFill(float x, float y, float width, float height, float angle, MyMath::Vector4 color);

	//�p�C�v���C���쐬
	std::unique_ptr < PipelineSet> CreatPipeline(D3D12_PRIMITIVE_TOPOLOGY_TYPE type, BlendMode mode);

	///<summary>
	///�o�b�t�@�쐬
	///</summary>
	///<param name="vertexCount">: ���_��</param>
	///<param name="indexCount">: �C���f�b�N�X��</param>
	///<returns>�o�b�t�@</returns>
	std::unique_ptr <Buff> CreateBuff(UINT vertexCount, UINT indexCount);


	//�e��p�C�v���C���Z�b�g����
	void CreatArryPipeline();

	//�萔�o�b�t�@����(2D���W�ϊ��s��)
	void CreatConstBuff();

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	Mesh& operator=(const Mesh&) = delete;
	Mesh(const Mesh&) = delete;
};



