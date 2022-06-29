#pragma once
//#DirectXのやつ
#include"ErrorException.h"

//自作.h
#include"MyMath.h"
#include"WindowsApp.h"
#include"DirectX12Core.h"

//pragma comment



//using namespace




class Sprite2D
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
	//ワールド行列
	//定数バッファのGPUリソースのポインタ
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffTransform = nullptr;
	//定数バッファのマッピング用ポインタ
	SpriteConstBufferDataTransform* constMapTransform = nullptr;
	//計算用ワールド座標
	MyMath::Matrix4 world;
	//計算用射影行列
	MyMath::Matrix4 projection;
public:
	///<summary>
	///初期化
	///</summary>
	///<param name="filePath">ファイルパス</param>
	Sprite2D(const wchar_t* filePath);

	///<summary>
	///更新
	///</summary>
	///<param name="pos">座標</param>
	///<param name="rot">回転</param>
	///<param name="scale">拡大率</param>
	/// ///<param name="color"> カラー</param>
	void Update(const MyMath::Vector3& pos = { 0.0f, 0.0f, 0.0f }, const MyMath::Vector3& rot = { 0.0f, 0.0f, 0.0f }, const MyMath::Vector3& scale = { 1.0f,1.0f, 1.0f }, const MyMath::Vector4& color = { 1.0f,1.0f, 1.0f, 1.0f});

	///<summary>
	///描画
	///</summary>
	void Draw();



private:

	//パイプラインの生成
	void CreatPipeline();
	//デスクプリタヒープの生成
	void CreateDescriptorHeap();
	//デスクプリタレンジの生成
	void CreateDescriptorRange();
	//シェーダ－リソースビュー生成
	void CreateShaderResourceView();
	//定数バッファ生成(2D座標変換行列)
	void CreatConstBuff();
	//頂点バッファ・インデックス生成
	void CreatVertexIndexBuffer();
	//テクスチャバッファ生成
	void CreatTextureBuffer();

	//コピーコンストラクタ・代入演算子削除
	Sprite2D& operator=(const Sprite2D&) = delete;
	Sprite2D(const Sprite2D&) = delete;
};

