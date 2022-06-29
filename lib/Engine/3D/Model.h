#pragma once
#include"MyMath.h"
#include"Camera.h"
#include"DirectX12Core.h"
#include"WindowsApp.h"

enum ModelShape
{
Cube,//立方体
Sphere,//球
Capsule,
Cylinder,

};

class Model
{

private:

	HRESULT result;
	char PADDING[4];
	ID3D12Device* device = nullptr;
	ID3D12GraphicsCommandList* cmdList = nullptr;
	DirectX::TexMetadata metadata{};
	DirectX::ScratchImage scratchImg{};
	DirectX::ScratchImage mipChain{};

	//パイプラインステート
	static Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState;
	//ルートシグネチャ
	static ID3D12RootSignature* rootSignature;
	//SRVの最大個数
	static const size_t kMaxSRVCount;
	//デスクプリタヒープ
	static ID3D12DescriptorHeap* srvHeap;
	//デスクプリタレンジ
	static D3D12_DESCRIPTOR_RANGE descriptorRange;
	//スプライト数
	static UINT nextIndex;

	//頂点バッファ
	Microsoft::WRL::ComPtr<ID3D12Resource> vertBuff;
	//頂点マップ
	PosUvColor* vertMap;
	//頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	//インデックスバッファの生成
	Microsoft::WRL::ComPtr<ID3D12Resource> indexBuff;
	////インデックスバッファをマッピング
	uint16_t* indexMap;
	//インデックスバッファビューの作成
	D3D12_INDEX_BUFFER_VIEW ibView{};
	//テクスチャバッファ
	ID3D12Resource* texBuff = nullptr;
	//GPUデスクプリタハンドル
	D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle;
	//CPUデスクプリタハンドル
	D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle;
	//定数バッファのGPUリソースのポインタ
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffTransform = nullptr;
	//定数バッファのマッピング用ポインタ
	SpriteConstBufferDataTransform* constMapTransform = nullptr;
	char PADDING1[4];
	//インデックスの数
	UINT maxIndex;
	char PADDING2[4];
	//頂点の数
	UINT maxVert;

	//キューブのインデックス数と頂点数
	const UINT cubeMaxIndex = 36;
	const UINT cubeMaxVert = 24;

public:
	Model();
	~Model();

	/// <summary>
	/// オブジェクト生成
	/// </summary>
	/// <param name="shape">生成するオブジェクトの種類</param>
	void Create(ModelShape shape);

	/// <summary>
	/// オブジェクトにテクスチャをセットする
	/// </summary>
	/// <param name="filePath">テクスチャまでのファイルパス</param>
	void SetTexture(const wchar_t* filePath);

	///<summary>
	///更新
	///</summary>
	///<param name="pos">座標</param>
	///<param name="rot">回転</param>
	///<param name="scale">拡大率</param>
	/// ///<param name="color"> カラー</param>
	void Update(const MyMath::Vector3& pos = { 0.0f, 0.0f, 0.0f }, const MyMath::Vector3& rot = { 0.0f, 0.0f, 0.0f }, const MyMath::Vector3& scale = { 1.0f,1.0f, 1.0f }, const MyMath::Vector4& color = { 1.0f,1.0f, 1.0f, 1.0f });

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="camera">カメラ</param>
	void Draw(Camera*& camera);

private:
	//キューブ生成
	void CreateCube();

	//パイプラインの生成
	void CreatPipeline();
	//デスクプリタヒープの生成
	void CreateDescriptorHeap();
	//デスクプリタレンジの生成
	void CreateDescriptorRange();
	//シェーダ－リソースビュー生成
	void CreateShaderResourceView();
	//頂点バッファ・インデックス生成
	void CreatVertexIndexBuffer();
	//テクスチャバッファ生成
	void CreatTextureBuffer();

	//コピーコンストラクタ・代入演算子削除
	Model& operator=(const Model&) = delete;
	Model(const Model&) = delete;
};

