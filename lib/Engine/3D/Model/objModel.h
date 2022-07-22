#pragma once
#include"Model.h"
#include"MyMath.h"

class objModel : public Model
{
private:

public:

	objModel();
	~objModel();

	/// <summary>
	/// �I�u�W�F�N�g����
	/// </summary>
	virtual void Create(const char* filePath, bool smoothing = false)override;

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
	virtual void Update(const MyMath::Vector3& pos = { 0.0f, 0.0f, 0.0f }, const MyMath::Vector3& rot = { 0.0f, 0.0f, 0.0f }, const MyMath::Vector3& scale = { 1.0f,1.0f, 1.0f })override;

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
	virtual void Initialize(ModelShareVaria& modelShareVaria)override;

	/// <summary>
	/// ���_���W���擾
	/// </summary>
	/// <returns>���_���W�z��</returns>
	virtual const std::vector<PosNormalUv>GetVertices()override;

	/// <summary>
	/// �C���f�b�N�X���擾
	/// </summary>
	/// <returns>�C���f�b�N�X���W�z��</returns>
	virtual const std::vector<uint16_t>GetIndices()override;

	/// <summary>
	/// �V�F�[�f�B���O�ݒ�
	/// </summary>
	/// <param name="type">�V�F�[�f�B���O�^�C�v</param>
	virtual	void SetShading(ShaderType type)override;

private:

	void LoadMaterial(const std::string& directoryPath,const std::string& filename);
	void LoadTexture(const std::string& directoryPath, const std::string& filename);

	//�V�F�[�_�|���\�[�X�r���[����
	virtual void CreateShaderResourceView()override;
	//���_�o�b�t�@�E�C���f�b�N�X����
	virtual void CreatVertexIndexBuffer()override;
	//�e�N�X�`���o�b�t�@����
	virtual void CreatTextureBuffer()override;

	virtual void Create(bool smoothing)override
	{
		static_cast<void>(smoothing);
	};

	void CalculateSmoothedVertexNormals();

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	objModel& operator=(const objModel&) = delete;
	objModel(const objModel&) = delete;
};

