#pragma once
#include "Model.h"
#include"DirectX12Core.h"

class ModelCone : public Model
{
private:
	//円錐のインデックス数と頂点数
	const UINT coneMaxIndex = 191;
	const UINT coneMaxVert = 66;

public:

	ModelCone();
	~ModelCone();

	/// <summary>
	/// オブジェクト生成
	/// </summary>
	virtual void Create()override;

	/// <summary>
	/// オブジェクトにテクスチャをセットする
	/// </summary>
	/// <param name="filePath">テクスチャまでのファイルパス</param>
	virtual void SetTexture(const wchar_t* filePath)override;

	///<summary>
	///更新
	///</summary>
	///<param name="pos">座標</param>
	///<param name="rot">回転</param>
	///<param name="scale">拡大率</param>
	/// ///<param name="color"> カラー</param>
	virtual void Update(const MyMath::Vector3& pos = { 0.0f, 0.0f, 0.0f }, const MyMath::Vector3& rot = { 0.0f, 0.0f, 0.0f }, const MyMath::Vector3& scale = { 1.0f,1.0f, 1.0f }, const MyMath::Vector4& color = { 1.0f,1.0f, 1.0f, 1.0f })override;

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="camera">カメラ</param>
	virtual void Draw(Camera* camera)override;

	/// <summary>
	/// ワールド行列の取得
	/// </summary>
	/// <returns>ワールド行列</returns>
	virtual MyMath::Matrix4& GetMatWorld()override;

	//初期化
	virtual void Initialize(ModelShareVaria& modelShareVaria)override;

	/// <summary>
	/// 頂点座標を取得
	/// </summary>
	/// <returns>頂点座標配列</returns>
	virtual const std::vector<PosUvColor>GetVertices()override;

	/// <summary>
	/// インデックスを取得
	/// </summary>
	/// <returns>インデックス座標配列</returns>
	virtual const std::vector<uint16_t>GetIndices()override;

private:

	//シェーダ－リソースビュー生成
	virtual void CreateShaderResourceView()override;
	//頂点バッファ・インデックス生成
	virtual void CreatVertexIndexBuffer()override;
	//テクスチャバッファ生成
	virtual void CreatTextureBuffer()override;

	virtual void Create(const char* filePath);

	void Initialize(ModelShareVaria& modelShareVaria, ID3D12PipelineState* pipelineState_, ID3D12RootSignature* rootSignature_)override;

	//コピーコンストラクタ・代入演算子削除
	ModelCone& operator=(const ModelCone&) = delete;
	ModelCone(const ModelCone&) = delete;
};

