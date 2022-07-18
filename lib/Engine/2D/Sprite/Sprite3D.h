#pragma once
//#DirectX�̂��
#include"ErrorException.h"

//����.h
#include"MyMath.h"
#include"WindowsApp.h"
#include"DirectX12Core.h"
#include "Camera.h"
#include"Sprite.h"
//pragma comment



//using namespace


class Sprite3D : public Sprite
{
private:

	MyMath::Matrix4 mTrans, mRot, mScale;

public:

	Sprite3D() = default;
	~Sprite3D() = default;

	//������
	virtual void Initialize(ModelShareVaria& modelShareVaria)override;

	///<summary>
	///�ǂݍ���
	///</summary>
	///<param name="filePath">�t�@�C���p�X</param>
	virtual void Load(const wchar_t* filePath)override;

	///<summary>
	///�X�V
	///</summary>
	///<param name="pos">���W</param>
	///<param name="rot">��]</param>
	///<param name="scale">�g�嗦</param>
	/// ///<param name="color"> �J���[</param>
	virtual void Update(const MyMath::Vector3& pos = { 0.0f, 0.0f, 0.0f }, const MyMath::Vector3& rot = { 0.0f, 0.0f, 0.0f }, const MyMath::Vector3& scale = { 1.0f,1.0f, 1.0f }, const MyMath::Vector4& color = { 1.0f,1.0f, 1.0f, 1.0f })override;

	///<summary>
	///�`��
	///</summary>
	virtual void Draw(Camera* camera)override;

	///<summary>
	///�r���{�[�h�`��
	///</summary>
	virtual void BillboardDraw(Camera* camera)override;

	///<summary>
	///X���r���{�[�h�`��
	///</summary>
	virtual void BillboardXDraw(Camera* camera)override;

	///<summary>
	///Y���r���{�[�h�`��
	///</summary>
	virtual void BillboardYDraw(Camera* camera)override;

	///<summary>
	///Z���r���{�[�h�`��
	///</summary>
	virtual void BillboardZDraw(Camera* camera)override;

private:

	//�V�F�[�_�|���\�[�X�r���[����
	virtual void CreateShaderResourceView();
	//�萔�o�b�t�@����(2D���W�ϊ��s��)
	virtual void CreatConstBuff();
	//���_�o�b�t�@�E�C���f�b�N�X����
	virtual void CreatVertexIndexBuffer();
	//�e�N�X�`���o�b�t�@����
	virtual void CreatTextureBuffer();

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	Sprite3D& operator=(const Sprite3D&) = delete;
	Sprite3D(const Sprite3D&) = delete;
};

