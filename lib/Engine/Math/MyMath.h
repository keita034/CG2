#pragma once
#include"ErrorException.h"

#include"Vector2.h"
#include"Vector3.h"
#include"Vector4.h"
#include"Matrix4.h"

namespace MyMath
{
	//��
	constexpr float AX_PIF = 3.141592654f;
	constexpr float AX_2PIF = 6.283185307f;
	constexpr double AX_PI = 3.141592654;
	constexpr double AX_2PI = 6.283185307;

	/// <summary>
	/// Sin�ACos�𗼕��o��
	/// </summary>
	/// <param name="sin_"> : sin�̌��ʂ�������</param>
	/// <param name="cos_"> : cos�̌��ʂ�������</param>
	/// <param name="angle"> : ���W�A���p</param>
	void SinCos(float& sin_, float& cos_, float angle);

	/// <summary>
	/// �x���@���烉�W�A���ϊ�
	/// </summary>
	/// <param name="angle"> : �p�x</param>
	float ChangeRadians(const float& angle);

	/// <summary>
	/// ���W�A������x���@�ϊ�
	/// </summary>
	/// <param name="angle"> : �p�x</param>
	float ChangeDira(const float& angle);

	/// <summary>
	/// �f�B���N�g������t�@�C�����ꗗ������
	/// </summary>
	/// <param name="folderPath">�f�B���N�g���p�X</param>
	/// <returns>�t�@�C�����ꗗ</returns>
	std::vector<std::string> getFileNames(std::string folderPath);

	/// <summary>
	/// �l��͈͓��ɔ[�߂�
	/// </summary>
	/// <param name="Value">�l</param>
	/// <param name="low">�Œ�l</param>
	/// <param name="high">�ō��l</param>
	template<typename T>
	T Clamp(T Value, const T low, const T high)
	{
		if (high < Value)
		{
			Value = high;
		}
		if (Value < low)
		{
			Value = low;
		}
		return Value;
	}

	/// <summary>
	/// �x�N�g���ƍs��̊|���Z
	/// </summary>
	/// <param name="vec">�x�N�g��</param>
	/// <param name="mat">�s��</param>
	/// <returns>�v�Z���ꂽ�l</returns>
	Vector3 Vector3Trns(Vector3& vec, Matrix4& mat);

	/// <summary>
	/// �x�N�g���ƍs��̊|���Z
	/// </summary>
	/// <param name="vec">�x�N�g��</param>
	/// <param name="mat">�s��</param>
	/// <returns>�v�Z���ꂽ�l</returns>
	Vector4 Vector4Trns(Vector4& vec, Matrix4& mat);
}

//���W�ϊ��s��
struct ConstBufferDataTransform
{
	MyMath::Matrix4 mat;//3D�ϊ��s��
};


struct PosNormalUv
{
	MyMath::Vector3 pos;//���W
	MyMath::Vector3 normal;//�@���x�N�g��
	MyMath::Vector2 uv;//uv���W
};

//���W�EUV�E�J���[
struct PosUvColor
{
	MyMath::Vector3 pos;//���W
	MyMath::Vector2 uv;//uv���W
	MyMath::Vector4 color;//�J���[
};

typedef struct
{
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
}ModelShareVaria;

//�p�C�v���C���E���[�g�V�O�l�`���Z�b�g
struct PipelineSet
{
	//�p�C�v���C���X�e�[�g
	Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState;
	//���[�g�V�O�l�`��
	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature;
};

struct worldViewpojCamera
{
	//���[���h�s��
	MyMath::Matrix4 world;
	//���[���h���W
	MyMath::Matrix4 matWorld;
	//�J�������W(���[���h���W)
	MyMath::Vector3 cameraPos;
};

//�}�e���A��
struct Material
{
	//�}�e���A����
	std::string name;
	//�A���r�G���g�e���x
	MyMath::Vector3 ambient = { 0.3f, 0.3f, 0.3f };
	//�f�B�t���[�Y�e���x
	MyMath::Vector3 diffuse = { 0.8f,0.8f,0.8f };
	//�X�y�L�����[�e���x
	MyMath::Vector3 specular = { 0.5f,0.5f,0.5f };
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