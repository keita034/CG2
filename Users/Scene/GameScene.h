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
	/// 初期化
	/// </summary>
	void Initialize();
	
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:

	//コピーコンストラクタ・代入演算子削除
	GameScene& operator=(const GameScene&) = delete;
	GameScene(const GameScene&) = delete;
};

