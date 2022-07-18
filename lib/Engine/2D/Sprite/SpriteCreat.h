#pragma once
#include"Sprite.h"
#include"MyMath.h"
#include"DirectX12Core.h"

class SpriteCreat
{
private:

	static ModelShareVaria modelShareVaria;

public:
	static Sprite* CreateSprite(const wchar_t* filePath, bool flag3d);

private:
	//�p�C�v���C���̐���
	static void CreatPipeline();
	//�f�X�N�v���^�q�[�v�̐���
	static void CreateDescriptorHeap();
	//�f�X�N�v���^�����W�̐���
	static void CreateDescriptorRange();
};

