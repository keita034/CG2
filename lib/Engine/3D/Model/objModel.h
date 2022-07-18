#pragma once
#include"Model.h"
#include"DirectX12Core.h"

//マテリアル
struct Material
{
	//マテリアル名
	std::string name;
	//アンビエント影響度
	MyMath::Vector3 ambient = { 0.3f,0.3f,0.3f };
	//ディフューズ影響度
	MyMath::Vector3 diffuse = { 0.0f,0.0f,0.0f };
	//スペキュラー影響度
	MyMath::Vector3 specular = { 0.0f,0.0f,0.0f };
	//アルファ
	float alpha = 1.0f;
	//テクスチャファイル名
	std::string textureFiename;
};

//マテリアルよう定数バッファ構造体
struct ConstBuffDataMaterial
{
	//アンビエント係数
	MyMath::Vector3 ambient;
	//パディング
	float pad1;
	//ディフューズ係数
	MyMath::Vector3 diffuse;
	//パディング
	float pad2;
	//スペキュラー係数
	MyMath::Vector3 specular;
	//アルファ
	float alpha;
};

class objModel : public Model
{
private:

	//マテリアル
	Material material{};

	//定数バッファマテリアル
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffMaterial;

	ConstBuffDataMaterial* constMapMaterial = nullptr;

public:

	objModel();
	~objModel();

	/// <summary>
	/// オブジェクト生成
	/// </summary>
	virtual void Create(const char* filePath)override;

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

	/// ワールド行列の取得
	/// </summary>
	/// <returns>ワールド行列</returns>
	virtual MyMath::Matrix4& GetMatWorld()override;

	//初期化
	void Initialize(ModelShareVaria& modelShareVaria, ID3D12PipelineState* pipelineState_, ID3D12RootSignature* rootSignature_)override;

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

	void LoadMaterial(const std::string& directoryPath,const std::string& filename);
	void LoadTexture(const std::string& directoryPath, const std::string& filename);

	//シェーダ－リソースビュー生成
	virtual void CreateShaderResourceView()override;
	//頂点バッファ・インデックス生成
	virtual void CreatVertexIndexBuffer()override;
	//テクスチャバッファ生成
	virtual void CreatTextureBuffer()override;

	virtual void Initialize(ModelShareVaria& modelShareVaria)override;

	virtual void Create()override
	{
	};

	//コピーコンストラクタ・代入演算子削除
	objModel& operator=(const objModel&) = delete;
	objModel(const objModel&) = delete;
};

