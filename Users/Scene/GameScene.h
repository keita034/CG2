#pragma once

#include "ErrorException.h"
#include"Model.h"
#include"ModelCreate.h"
#include"Camera.h"
#include"CollisionPrimitive.h"
#include"Input.h"
#include"SpriteCreat.h"
#include"ParticleCreat.h"
class GameScene
{
private:

	std::unique_ptr<Model> skyDome;
	std::unique_ptr<Model> ground;
	std::unique_ptr<Camera> camera;
	std::unique_ptr<Sprite> sprite;
	std::unique_ptr<Particle> particle;
	Input* input = nullptr;

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

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	GameScene& operator=(const GameScene&) = delete;
	GameScene(const GameScene&) = delete;
};

