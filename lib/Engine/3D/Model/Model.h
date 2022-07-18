#pragma once
#include"ErrorException.h"
#include"MyMath.h"
#include"Camera.h"

enum class ModelShape
{
	Cube,//������
	Sphere,//��
	Capsule,//�J�v�Z��
	Cylinder,//�~��
	Cone,//�~��
};

class Model
{
protected:

	HRESULT result;
	char PADDING[4];
	Microsoft::WRL::ComPtr<ID3D12Device> device;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> cmdList;
	DirectX::TexMetadata metadata{};
	DirectX::ScratchImage scratchImg{};
	DirectX::ScratchImage mipChain{};

	//�p�C�v���C���X�e�[�g
	Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState;
	//���[�g�V�O�l�`��
	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature;
	//�f�X�N�v���^�q�[�v
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvHeap;
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
	Microsoft::WRL::ComPtr<ID3D12Resource> texBuff;
	//GPU�f�X�N�v���^�n���h��
	D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle;
	//CPU�f�X�N�v���^�n���h��
	D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle;
	//�萔�o�b�t�@��GPU���\�[�X�̃|�C���^
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffTransform;
	//�萔�o�b�t�@�̃}�b�s���O�p�|�C���^
	ConstBufferDataTransform* constMapTransform = nullptr;
	char PADDING1[4];
	//�C���f�b�N�X�̐�
	UINT maxIndex;
	char PADDING2[4];
	//���_�̐�
	UINT maxVert;
	//���[���h�s��
	MyMath::Matrix4 matWorld;
	//���O
	const char* name = nullptr;
	//���_�f�[�^
	std::vector<PosUvColor>vertices;
	//���_�C���f�b�N�X
	std::vector<uint16_t> indices;


public:

	/// <summary>
	/// �I�u�W�F�N�g����
	/// </summary>
	virtual void Create() = 0;

	/// <summary>
	/// �I�u�W�F�N�g����
	/// </summary>
	/// <param name="filePath">�I�u�W�F�N�g�܂ł̃t�@�C���p�X</param>
	virtual void Create(const char* filePath) = 0;

	/// <summary>
	/// �I�u�W�F�N�g�Ƀe�N�X�`�����Z�b�g����
	/// </summary>
	/// <param name="filePath">�e�N�X�`���܂ł̃t�@�C���p�X</param>
	virtual void SetTexture(const wchar_t* filePath) = 0;

	///<summary>
	///�X�V
	///</summary>
	///<param name="pos">���W</param>
	///<param name="rot">��]</param>
	///<param name="scale">�g�嗦</param>
	/// ///<param name="color"> �J���[</param>
	virtual void Update(const MyMath::Vector3& pos = { 0.0f, 0.0f, 0.0f }, const MyMath::Vector3& rot = { 0.0f, 0.0f, 0.0f }, const MyMath::Vector3& scale = { 1.0f,1.0f, 1.0f }, const MyMath::Vector4& color = { 1.0f,1.0f, 1.0f, 1.0f }) = 0;

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="camera">�J����</param>
	virtual void Draw(Camera* camera) = 0;

	/// <summary>
	/// ���[���h�s��̎擾
	/// </summary>
	/// <returns>���[���h�s��</returns>
	virtual MyMath::Matrix4& GetMatWorld() = 0;

	//������
	virtual void Initialize(ModelShareVaria& modelShareVaria) = 0;

	//������
	virtual void Initialize(ModelShareVaria& modelShareVaria, ID3D12PipelineState* pipelineState_, ID3D12RootSignature* rootSignature_) = 0;

	/// <summary>
	/// ���_���W���擾
	/// </summary>
	/// <returns>���_���W�z��</returns>
	virtual const std::vector<PosUvColor>GetVertices() = 0;

	/// <summary>
	/// �C���f�b�N�X���擾
	/// </summary>
	/// <returns>�C���f�b�N�X���W�z��</returns>
	virtual const std::vector<uint16_t>GetIndices() = 0;

	Model() = default;
	virtual ~Model()= default;

protected:

	//�V�F�[�_�|���\�[�X�r���[����
	virtual void CreateShaderResourceView() = 0;
	//���_�o�b�t�@�E�C���f�b�N�X����
	virtual void CreatVertexIndexBuffer() = 0;
	//�e�N�X�`���o�b�t�@����
	virtual void CreatTextureBuffer() = 0;


	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	Model& operator=(const Model&) = delete;
	Model(const Model&) = delete;
};