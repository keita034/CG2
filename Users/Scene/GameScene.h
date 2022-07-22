#pragma once

#include "ErrorException.h"
#include"Model.h"
#include"ModelCreate.h"
#include"Camera.h"
#include"CollisionPrimitive.h"
#include"Input.h"
#include"SpriteCreat.h"
#include"ParticleCreat.h"
#include"Light.h"
#include"Mesh.h"

class GameScene
{
private:
	//========����========//

	//�V�[���t���O
	uint16_t sceneFlag = 0;
	char PADDING[6]{};
	Input* input = nullptr;
	Mesh* mesh = nullptr;
	std::unique_ptr<Camera> camera;
	std::unique_ptr<Light> light;
	MyMath::Vector4 lightColor = { 1, 1, 1, 1 };
	std::unique_ptr<Model> skydome;

	//====================//

	//======�K�{�ۑ�======//

	//�O�p�`�̐F
	MyMath::Vector4 triangleColor = { 255.0f,255.0f,255.0f,255.0f };
	float sin = 0.0f;
	float cos = 0.0f;

	//===================//

	//=====�}�`�`��=====//

	//��̒��S�̍��W
	MyMath::Vector2 faceCenter = { 900.0f ,350.0f };
	//��̔��a
	MyMath::Vector2 faceRadius = { 100.0f ,100.0f };
	//�@�̍��W
	MyMath::Vector2 nose[3] = { {900.0f,330.0f},{885.0f,370.0f},{915.0f,370.0f} };
	//�ڂ̍��W
	MyMath::Vector2 eye[3] = { {900.0f,295.0f},{885.0f,330.0f},{915.0f,330.0f} };
	//�ڂ����S�ŕ`�悳���̂ł��炷��
	float eyeShift = 45.0f;
	//���̍��W
	MyMath::Vector2 mouth[3] = { {900.0f,425.0f},{885.0f,400.0f},{915.0f,400.0f} };
	//���C���[�t���[���t���O
	bool wireFrameFlag = true;
	char PADDING1[3]{};
	//�A���t�@�̒l
	int alphaNum = 255;
	char PADDING2[4]{};
	//=================//

	//=�X�v���C�g�`��==//
	//���s���e�ŕ`�悳���X�v���C�g
	std::unique_ptr<Sprite> sprite2D;
	//���W
	MyMath::Vector3 sprite2DPos = { 320.0f,360.0f,0.0f };
	//��]�p
	MyMath::Vector3 sprite2DRot = { 0.0f,0.0f,0.0f };
	//�X�P�[��
	MyMath::Vector3 sprite2DSca = { 0.5f,0.5f,0.5f };
	char PADDING3[4]{};

	//�ˉe���e�ŕ`�悳���X�v���C�g
	std::unique_ptr<Sprite> sprite3D;
	//���W
	MyMath::Vector3 sprite3DPos = { 0.0f,0.0f,0.0f };
	//��]�p
	MyMath::Vector3 sprite3DRot = { 0.0f,0.0f,0.0f };
	//�X�P�[��
	MyMath::Vector3 sprite3DSca = { 0.5f,0.5f,0.5f };
	char PADDING4[4]{};

	//�r���{�[�h�ŕ`�悳���X�v���C�g
	std::unique_ptr<Sprite> spriteBillboard;
	//���W
	MyMath::Vector3 spriteBillboardPos = { 40.0f,0.0f,0.0f };
	//��]�p
	MyMath::Vector3 spriteBillboardRot = { 0.0f,0.0f,0.0f };
	//�X�P�[��
	MyMath::Vector3 spriteBillboardSca = { 0.5f,0.5f,0.5f };
	char PADDING5[4]{};
	//================//

	//�v���~�e�B�u�`��//
	
	//�L���[�u
	std::unique_ptr<Model> cube;
	//��
	std::unique_ptr<Model> sphere;
	//�~��
	std::unique_ptr<Model> cylinder;
	//�R�[��
	std::unique_ptr<Model> cone;
	//���W
	MyMath::Vector3 modelPos = { 0.0f,0.0f,-90.0f };
	//��]�p
	MyMath::Vector3 modelRot = { 0.0f,0.0f,0.0f };
	//�X�P�[��
	MyMath::Vector3 modelSca = { 1.0f,1.0f,1.0f };
	//���f���̌`
	ModelShape modelType = ModelShape::Cube;

	//================//

	//===���f���`��===//

	//�X���[�W���O���郂�f��
	std::unique_ptr<Model> objModel1;
	//�X���[�W���O���Ȃ����f��
	std::unique_ptr<Model> objModel2;
	//���W
	MyMath::Vector3 objModelPos = { 0.0f,0.0f,-90.0f };
	//��]�p
	MyMath::Vector3 objModelRot = { 0.0f,0.0f,0.0f };
	//�X�P�[��
	MyMath::Vector3 objModelSca = { 1.0f,1.0f,1.0f };
	//���S�ŕ`�悳���̂ł��炷��
	MyMath::Vector3 objModelPosShift = { 2.0f,0.0f,0.0f };

	//================//

public:

	GameScene();
	~GameScene();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

private:

	//�}�`�ړ�
	void MeshMove();
	
	//�J�����ړ�
	MyMath::Vector3 CameraMove();

	//���f���ړ�
	void ModelMove();
	
	void ObjMove();

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	GameScene& operator=(const GameScene&) = delete;
	GameScene(const GameScene&) = delete;
};

