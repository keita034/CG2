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

//���W�EUV
struct PosUvColor
{
	MyMath::Vector3 pos;//���W
	MyMath::Vector3 normal;//�@���x�N�g��
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