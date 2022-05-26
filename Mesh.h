#pragma once
#include <d3d12.h>
#include<DirectXMath.h>

struct PosColr
{
	DirectX::XMFLOAT3 pos;//座標
	DirectX::XMFLOAT4 colr;//カラー
};

struct PipelineSet
{
	//パイプラインステート
	ID3D12PipelineState* pipelineState;
	//ルートシグネチャ
	ID3D12RootSignature* rootSignature;
};

struct Buff
{
	//頂点バッファ
	ID3D12Resource* vertBuff;
	//頂点マップ
	PosColr* vertMap;
	//頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView;
	//インデックスバッファの生成
	ID3D12Resource* indexBuff;
	////インデックスバッファをマッピング
	uint16_t* indexMap;
	//インデックスバッファビューの作成
	D3D12_INDEX_BUFFER_VIEW ibView;
};

enum BlendMode
{
	BLENDMODE_NOBLEND,//ノーブレンド（デフォルト）
	BLENDMODE_ALPHA,//αブレンド
	BLENDMODE_ADD,//加算ブレンド
	BLENDMODE_SUB,//減算ブレンド
	BLENDMODE_MULA,//乗算ブレンド
	BLENDMODE_INVSRC//反転ブレンド
};

class Mesh
{
public:
	void DrawTriangle(float x1,float y1, float x2, float y2, float x3, float y3, DirectX::XMFLOAT4 colr);
	void DrawTriangleUpdate();
	Mesh(DX12Base* base);
private:

	//頂点バッファ
	ID3D12Resource* vertBuff;
	//頂点マップ
	PosColr* vertMap;
	//頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView;
	//インデックスバッファの生成
	ID3D12Resource* indexBuff;
	////インデックスバッファをマッピング
	uint16_t* indexMap;
	//インデックスバッファビューの作成
	D3D12_INDEX_BUFFER_VIEW ibView;

	//パイプラインステート
	ID3D12PipelineState* pipelineState;
	//ルートシグネチャ
	ID3D12RootSignature* rootSignature;

	//三角形描画上限
	UINT maxCount = 2048;
	//三角形頂点数
	UINT VertexCount = 3;

	UINT count = 0;

	ID3D12Device* device = nullptr;

	ID3D12GraphicsCommandList* commandList = nullptr;

	void CreatPipeline();

	void CreateBuff();
};

