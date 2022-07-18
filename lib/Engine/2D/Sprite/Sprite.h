#pragma once
#include"ErrorException.h"
#include"MyMath.h"
#include"Camera.h"

class Sprite
{
protected:
	HRESULT result;
	char PADDING[4];
	Microsoft::WRL::ComPtr<ID3D12Device> device;
	Microsoft::WRL::ComPtr <ID3D12GraphicsCommandList> cmdList = nullptr;
	DirectX::TexMetadata metadata{};
	DirectX::ScratchImage scratchImg{};
	DirectX::ScratchImage mipChain{};

	//�p�C�v���C���X�e�[�g
	Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState;
	//���[�g�V�O�l�`��
	Microsoft::WRL::ComPtr <ID3D12RootSignature> rootSignature;
	//�f�X�N�v���^�q�[�v
	Microsoft::WRL::ComPtr <ID3D12DescriptorHeap> srvHeap;
	//�f�X�N�v���^�����W
	D3D12_DESCRIPTOR_RANGE descriptorRange;
	//�X�v���C�g��
	UINT nextIndex;

	//���_�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource> vertBuff;
	//���_�}�b�v
	PosUvColor* vertMap;
	//���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	//�C���f�b�N�X�o�b�t�@�̐���
	Microsoft::WRL::ComPtr<ID3D12Resource> indexBuff;
	////�C���f�b�N�X�o�b�t�@���}�b�s���O
	uint16_t* indexMap;
	//�C���f�b�N�X�o�b�t�@�r���[�̍쐬
	D3D12_INDEX_BUFFER_VIEW ibView{};
	//�e�N�X�`���o�b�t�@
	Microsoft::WRL::ComPtr <ID3D12Resource> texBuff = nullptr;
	//GPU�f�X�N�v���^�n���h��
	D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle;
	//CPU�f�X�N�v���^�n���h��
	D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle;
	//�萔�o�b�t�@��GPU���\�[�X�̃|�C���^
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffTransform = nullptr;
	//�萔�o�b�t�@�̃}�b�s���O�p�|�C���^
	ConstBufferDataTransform* constMapTransform = nullptr;
	//���[���h���W
	MyMath::Matrix4 matWorld;
	//�v���W�F�N�V�����s��
	MyMath::Matrix4 matProjection;
public:

	Sprite()= default;

	virtual ~Sprite() = default;

	//������
	virtual void Initialize(ModelShareVaria& modelShareVaria) = 0;


	///<summary>
	///�ǂݍ���
	///</summary>
	///<param name="filePath">�t�@�C���p�X</param>
	virtual void Load(const wchar_t* filePath) = 0;

	///<summary>
	///�X�V
	///</summary>
	///<param name="pos">���W</param>
	///<param name="rot">��]</param>
	///<param name="scale">�g�嗦</param>
	/// ///<param name="color"> �J���[</param>
	virtual void Update(const MyMath::Vector3& pos = { 0.0f, 0.0f, 0.0f }, const MyMath::Vector3& rot = { 0.0f, 0.0f, 0.0f }, const MyMath::Vector3& scale = { 1.0f,1.0f, 1.0f }, const MyMath::Vector4& color = { 1.0f,1.0f, 1.0f, 1.0f }) = 0;

	///<summary>
	///�`��
	///</summary>
	virtual void Draw(Camera* camera) = 0;

	///<summary>
	///�r���{�[�h�`��
	///</summary>
	virtual void BillboardDraw(Camera* camera) = 0;

	///<summary>
	///X���r���{�[�h�`��
	///</summary>
	virtual void BillboardXDraw(Camera* camera) = 0;

	///<summary>
	///Y���r���{�[�h�`��
	///</summary>
	virtual void BillboardYDraw(Camera* camera) = 0;

	///<summary>
	///Z���r���{�[�h�`��
	///</summary>
	virtual void BillboardZDraw(Camera* camera) = 0;

protected:
	//�V�F�[�_�|���\�[�X�r���[����
	virtual void CreateShaderResourceView() = 0;
	//�萔�o�b�t�@����(2D���W�ϊ��s��)
	virtual void CreatConstBuff() = 0;
	//���_�o�b�t�@�E�C���f�b�N�X����
	virtual void CreatVertexIndexBuffer() = 0;
	//�e�N�X�`���o�b�t�@����
	virtual void CreatTextureBuffer() = 0;

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	Sprite& operator=(const Sprite&) = delete;
	Sprite(const Sprite&) = delete;
};