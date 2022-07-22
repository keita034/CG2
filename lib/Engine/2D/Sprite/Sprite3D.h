#pragma once
//#DirectXのやつ
#include"ErrorException.h"

//自作.h
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

	//初期化
	virtual void Initialize(ModelShareVaria& modelShareVaria)override;

	///<summary>
	///読み込み
	///</summary>
	///<param name="filePath">ファイルパス</param>
	virtual void Load(const wchar_t* filePath)override;

	///<summary>
	///更新
	///</summary>
	///<param name="pos">座標</param>
	///<param name="rot">回転</param>
	///<param name="scale">拡大率</param>
	/// ///<param name="color"> カラー</param>
	virtual void Update(const MyMath::Vector3& pos = { 0.0f, 0.0f, 0.0f }, const MyMath::Vector3& rot = { 0.0f, 0.0f, 0.0f }, const MyMath::Vector3& scale = { 1.0f,1.0f, 1.0f }, const MyMath::Vector4& color = { 1.0f,1.0f, 1.0f, 1.0f })override;

	///<summary>
	///描画
	///</summary>
	virtual void Draw(Camera* camera)override;

	///<summary>
	///ビルボード描画
	///</summary>
	virtual void BillboardDraw(Camera* camera)override;

	///<summary>
	///X軸ビルボード描画
	///</summary>
	virtual void BillboardXDraw(Camera* camera)override;

	///<summary>
	///Y軸ビルボード描画
	///</summary>
	virtual void BillboardYDraw(Camera* camera)override;

	///<summary>
	///Z軸ビルボード描画
	///</summary>
	virtual void BillboardZDraw(Camera* camera)override;

private:

	//シェーダ－リソースビュー生成
	virtual void CreateShaderResourceView();
	//定数バッファ生成(2D座標変換行列)
	virtual void CreatConstBuff();
	//頂点バッファ・インデックス生成
	virtual void CreatVertexIndexBuffer();
	//テクスチャバッファ生成
	virtual void CreatTextureBuffer();

	//コピーコンストラクタ・代入演算子削除
	Sprite3D& operator=(const Sprite3D&) = delete;
	Sprite3D(const Sprite3D&) = delete;
};

