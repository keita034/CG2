#pragma once
#include"Model.h"
#include"DirectX12Core.h"

//�}�e���A��
struct Material
{
	//�}�e���A����
	std::string name;
	//�A���r�G���g�e���x
	MyMath::Vector3 ambient = { 0.3f,0.3f,0.3f };
	//�f�B�t���[�Y�e���x
	MyMath::Vector3 diffuse = { 0.0f,0.0f,0.0f };
	//�X�y�L�����[�e���x
	MyMath::Vector3 specular = { 0.0f,0.0f,0.0f };
	//�A���t�@
	float alpha = 1.0f;
	//�e�N�X�`���t�@�C����
	std::string textureFiename;
};

//�}�e���A���悤�萔�o�b�t�@�\����
struct ConstBuffDataMaterial
{
	//�A���r�G���g�W��
	MyMath::Vector3 ambient;
	//�p�f�B���O
	float pad1;
	//�f�B�t���[�Y�W��
	MyMath::Vector3 diffuse;
	//�p�f�B���O
	float pad2;
	//�X�y�L�����[�W��
	MyMath::Vector3 specular;
	//�A���t�@
	float alpha;
};

class objModel : public Model
{
private:

	//�}�e���A��
	Material material{};

	//�萔�o�b�t�@�}�e���A��
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffMaterial;

	ConstBuffDataMaterial* constMapMaterial = nullptr;

public:

	objModel();
	~objModel();

	/// <summary>
	/// �I�u�W�F�N�g����
	/// </summary>
	virtual void Create(const char* filePath)override;

	/// <summary>
	/// �I�u�W�F�N�g�Ƀe�N�X�`�����Z�b�g����
	/// </summary>
	/// <param name="filePath">�e�N�X�`���܂ł̃t�@�C���p�X</param>
	virtual void SetTexture(const wchar_t* filePath)override;

	///<summary>
	///�X�V
	///</summary>
	///<param name="pos">���W</param>
	///<param name="rot">��]</param>
	///<param name="scale">�g�嗦</param>
	/// ///<param name="color"> �J���[</param>
	virtual void Update(const MyMath::Vector3& pos = { 0.0f, 0.0f, 0.0f }, const MyMath::Vector3& rot = { 0.0f, 0.0f, 0.0f }, const MyMath::Vector3& scale = { 1.0f,1.0f, 1.0f }, const MyMath::Vector4& color = { 1.0f,1.0f, 1.0f, 1.0f })override;

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="camera">�J����</param>
	virtual void Draw(Camera* camera)override;

	/// ���[���h�s��̎擾
	/// </summary>
	/// <returns>���[���h�s��</returns>
	virtual MyMath::Matrix4& GetMatWorld()override;

	//������
	void Initialize(ModelShareVaria& modelShareVaria, ID3D12PipelineState* pipelineState_, ID3D12RootSignature* rootSignature_)override;

	/// <summary>
	/// ���_���W���擾
	/// </summary>
	/// <returns>���_���W�z��</returns>
	virtual const std::vector<PosUvColor>GetVertices()override;

	/// <summary>
	/// �C���f�b�N�X���擾
	/// </summary>
	/// <returns>�C���f�b�N�X���W�z��</returns>
	virtual const std::vector<uint16_t>GetIndices()override;

private:

	void LoadMaterial(const std::string& directoryPath,const std::string& filename);
	void LoadTexture(const std::string& directoryPath, const std::string& filename);

	//�V�F�[�_�|���\�[�X�r���[����
	virtual void CreateShaderResourceView()override;
	//���_�o�b�t�@�E�C���f�b�N�X����
	virtual void CreatVertexIndexBuffer()override;
	//�e�N�X�`���o�b�t�@����
	virtual void CreatTextureBuffer()override;

	virtual void Initialize(ModelShareVaria& modelShareVaria)override;

	virtual void Create()override
	{
	};

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	objModel& operator=(const objModel&) = delete;
	objModel(const objModel&) = delete;
};

