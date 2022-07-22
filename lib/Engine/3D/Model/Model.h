#pragma once
#include"ErrorException.h"
#include"MyMath.h"
#include"Camera.h"
#include"ModelPipeLine.h"
#include"DirectX12Core.h"
#include"Light.h"

enum class ModelShape
{
	Cube,//立方体
	Sphere,//球
	Capsule,//カプセル
	Cylinder,//円柱
	Cone,//円錐
};

enum ShaderType
{
	Default,
	Flat,
	Gouraud,
	Lambert,
	Phong,

};

class Model
{
protected:

	HRESULT result;
	char PADDING[4];
	Microsoft::WRL::ComPtr<ID3D12Device> device;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> cmdList;
	DirectX::TexMetadata metadata{};
	DirectX::ScratchImage scratchImg{};
	DirectX::ScratchImage mipChain{};

	//パイプラインステート
	Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState;
	//ルートシグネチャ
	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature;
	//デスクプリタヒープ
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvHeap;
	//デスクプリタレンジ
	D3D12_DESCRIPTOR_RANGE descriptorRange;
	//スプライト数
	UINT nextIndex;

	//頂点バッファ
	Microsoft::WRL::ComPtr<ID3D12Resource> vertBuff;
	//頂点マップ
	PosNormalUv* vertMap;
	//頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	//インデックスバッファの生成
	Microsoft::WRL::ComPtr<ID3D12Resource> indexBuff;
	////インデックスバッファをマッピング
	uint16_t* indexMap;
	//インデックスバッファビューの作成
	D3D12_INDEX_BUFFER_VIEW ibView{};
	//テクスチャバッファ
	Microsoft::WRL::ComPtr<ID3D12Resource> texBuff;
	//GPUデスクプリタハンドル
	D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle;
	//CPUデスクプリタハンドル
	D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle;
	//定数バッファのGPUリソースのポインタ
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffTransform;
	//定数バッファのマッピング用ポインタ
	worldViewpojCamera* constMapTransform = nullptr;
	char PADDING1[4];
	//インデックスの数
	UINT maxIndex;
	char PADDING2[4];
	//頂点の数
	UINT maxVert;
	//ワールド行列
	MyMath::Matrix4 matWorld;
	//頂点データ
	std::vector<PosNormalUv>vertices;
	//頂点インデックス
	std::vector<uint16_t> indices;
	//頂点法線スムージング用データ
	std::unordered_map<uint16_t, std::vector<uint16_t>>smoothData;
	//ライト
	static Light* light;
	//マテリアル
	Material material{};
	//定数バッファマテリアル
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffMaterial;
	//定数バッファマテリアルのマッピング用ポインタ
	ConstBuffDataMaterial* constMapMaterial = nullptr;


public:

	/// <summary>
	/// オブジェクト生成
	/// </summary>
	virtual void Create(bool smoothing)= 0;

	/// <summary>
	/// オブジェクト生成
	/// </summary>
	/// <param name="filePath">オブジェクトまでのファイルパス</param>
	virtual void Create(const char* filePath, bool smoothing) = 0;

	/// <summary>
	/// オブジェクトにテクスチャをセットする
	/// </summary>
	/// <param name="filePath">テクスチャまでのファイルパス</param>
	virtual void SetTexture(const wchar_t* filePath) = 0;

	///<summary>
	///更新
	///</summary>
	///<param name="pos">座標</param>
	///<param name="rot">回転</param>
	///<param name="scale">拡大率</param>
	/// ///<param name="color"> カラー</param>
	virtual void Update(const MyMath::Vector3& pos = { 0.0f, 0.0f, 0.0f }, const MyMath::Vector3& rot = { 0.0f, 0.0f, 0.0f }, const MyMath::Vector3& scale = { 1.0f,1.0f, 1.0f }) = 0;

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="camera">カメラ</param>
	virtual void Draw(Camera* camera) = 0;

	/// <summary>
	/// ワールド行列の取得
	/// </summary>
	/// <returns>ワールド行列</returns>
	virtual MyMath::Matrix4& GetMatWorld() = 0;

	//初期化
	virtual void Initialize(ModelShareVaria& modelShareVaria) = 0;

	/// <summary>
	/// 頂点座標を取得
	/// </summary>
	/// <returns>頂点座標配列</returns>
	virtual const std::vector<PosNormalUv>GetVertices() = 0;

	/// <summary>
	/// インデックスを取得
	/// </summary>
	/// <returns>インデックス座標配列</returns>
	virtual const std::vector<uint16_t>GetIndices() = 0;

	/// <summary>
	/// シェーディング設定
	/// </summary>
	/// <param name="type">シェーディングタイプ</param>
	virtual void SetShading(ShaderType type) = 0;

	/// <summary>
	/// ライトのセット
	/// </summary>
	/// <param name="light">ライト</param>
	static void SetLight(Light* light_);

	Model() = default;
	virtual ~Model()= default;

protected:

	//シェーダ－リソースビュー生成
	virtual void CreateShaderResourceView() = 0;
	//頂点バッファ・インデックス生成
	virtual void CreatVertexIndexBuffer() = 0;
	//テクスチャバッファ生成
	virtual void CreatTextureBuffer() = 0;

	//コピーコンストラクタ・代入演算子削除
	Model& operator=(const Model&) = delete;
	Model(const Model&) = delete;
};