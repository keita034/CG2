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
	//========共通========//

	//シーンフラグ
	uint16_t sceneFlag = 0;
	char PADDING[6]{};
	Input* input = nullptr;
	Mesh* mesh = nullptr;
	std::unique_ptr<Camera> camera;
	std::unique_ptr<Light> light;
	MyMath::Vector4 lightColor = { 1, 1, 1, 1 };
	std::unique_ptr<Model> skydome;

	//====================//

	//======必須課題======//

	//三角形の色
	MyMath::Vector4 triangleColor = { 255.0f,255.0f,255.0f,255.0f };
	float sin = 0.0f;
	float cos = 0.0f;

	//===================//

	//=====図形描画=====//

	//顔の中心の座標
	MyMath::Vector2 faceCenter = { 900.0f ,350.0f };
	//顔の半径
	MyMath::Vector2 faceRadius = { 100.0f ,100.0f };
	//鼻の座標
	MyMath::Vector2 nose[3] = { {900.0f,330.0f},{885.0f,370.0f},{915.0f,370.0f} };
	//目の座標
	MyMath::Vector2 eye[3] = { {900.0f,295.0f},{885.0f,330.0f},{915.0f,330.0f} };
	//目が中心で描画されるのでずらす量
	float eyeShift = 45.0f;
	//口の座標
	MyMath::Vector2 mouth[3] = { {900.0f,425.0f},{885.0f,400.0f},{915.0f,400.0f} };
	//ワイヤーフレームフラグ
	bool wireFrameFlag = true;
	char PADDING1[3]{};
	//アルファの値
	int alphaNum = 255;
	char PADDING2[4]{};
	//=================//

	//=スプライト描画==//
	//平行投影で描画されるスプライト
	std::unique_ptr<Sprite> sprite2D;
	//座標
	MyMath::Vector3 sprite2DPos = { 320.0f,360.0f,0.0f };
	//回転角
	MyMath::Vector3 sprite2DRot = { 0.0f,0.0f,0.0f };
	//スケール
	MyMath::Vector3 sprite2DSca = { 0.5f,0.5f,0.5f };
	char PADDING3[4]{};

	//射影投影で描画されるスプライト
	std::unique_ptr<Sprite> sprite3D;
	//座標
	MyMath::Vector3 sprite3DPos = { 0.0f,0.0f,0.0f };
	//回転角
	MyMath::Vector3 sprite3DRot = { 0.0f,0.0f,0.0f };
	//スケール
	MyMath::Vector3 sprite3DSca = { 0.5f,0.5f,0.5f };
	char PADDING4[4]{};

	//ビルボードで描画されるスプライト
	std::unique_ptr<Sprite> spriteBillboard;
	//座標
	MyMath::Vector3 spriteBillboardPos = { 40.0f,0.0f,0.0f };
	//回転角
	MyMath::Vector3 spriteBillboardRot = { 0.0f,0.0f,0.0f };
	//スケール
	MyMath::Vector3 spriteBillboardSca = { 0.5f,0.5f,0.5f };
	char PADDING5[4]{};
	//================//

	//プリミティブ描画//
	
	//キューブ
	std::unique_ptr<Model> cube;
	//球
	std::unique_ptr<Model> sphere;
	//円柱
	std::unique_ptr<Model> cylinder;
	//コーン
	std::unique_ptr<Model> cone;
	//座標
	MyMath::Vector3 modelPos = { 0.0f,0.0f,-90.0f };
	//回転角
	MyMath::Vector3 modelRot = { 0.0f,0.0f,0.0f };
	//スケール
	MyMath::Vector3 modelSca = { 1.0f,1.0f,1.0f };
	//モデルの形
	ModelShape modelType = ModelShape::Cube;

	//================//

	//===モデル描画===//

	//スムージングするモデル
	std::unique_ptr<Model> objModel1;
	//スムージングしないモデル
	std::unique_ptr<Model> objModel2;
	//座標
	MyMath::Vector3 objModelPos = { 0.0f,0.0f,-90.0f };
	//回転角
	MyMath::Vector3 objModelRot = { 0.0f,0.0f,0.0f };
	//スケール
	MyMath::Vector3 objModelSca = { 1.0f,1.0f,1.0f };
	//中心で描画されるのでずらす量
	MyMath::Vector3 objModelPosShift = { 2.0f,0.0f,0.0f };

	//================//

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

	//図形移動
	void MeshMove();
	
	//カメラ移動
	MyMath::Vector3 CameraMove();

	//モデル移動
	void ModelMove();
	
	void ObjMove();

	//コピーコンストラクタ・代入演算子削除
	GameScene& operator=(const GameScene&) = delete;
	GameScene(const GameScene&) = delete;
};

