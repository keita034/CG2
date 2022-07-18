#pragma once
#pragma once
/// <summary>
///�����蔻��v���~�e�B�u
/// </summary>

#include"MyMath.h"

/// <summary>
/// ��
/// </summary>
struct Sphere
{
	//���S���W
	MyMath::Vector4 center = { 0.0f,0.0f,0.0f,1.0f };
	//���a
	float radius = 1.0f;
};

/// <summary>
/// ����
/// </summary>
struct Plane
{
	//�@���x�N�g��
	MyMath::Vector4 normal = { 0.0f,1.0f,0.0f,0.0f };
	//���_�_(0,0,0)����̋���
	float distance = 0.0f;
};

/// <summary>
/// �@���t���O�p�`(���v��肪�\��)
/// </summary>
struct Triangle
{
	//���_���W3��
	MyMath::Vector4 p0;
	MyMath::Vector4 p1;
	MyMath::Vector4 p2;
	//�@���x�N�g��
	MyMath::Vector4 normal;

	/// <summary>
	/// �@���̌v�Z
	/// </summary>
	void ComputeNormal();
};

/// <summary>
/// ���C(������)
/// </summary>
struct Ray
{
	//�n�_���W
	MyMath::Vector4 start = { 0,0,0,1 };
	//����
	MyMath::Vector4 dir = { 1,0,0,0};
};