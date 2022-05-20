#pragma once
#include<DirectXMath.h>
#include <Windows.h>
#include <d3dcompiler.h>
#include<d3d12.h>

struct VertexPosColor
{
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT4 color;
};

//ブレンドモード
enum BlendMode
{
	AE_BLENDMODE_NOBLEND,//ノーブレンド（デフォルト）
	AE_BLENDMODE_ALPHA,// αブレンド
	AE_BLENDMODE_ADD,// 加算ブレンド
	AE_BLENDMODE_SUB,// 減算ブレンド
	AE_BLENDMODE_MULA,// 乗算ブレンド
	AE_BLENDMODE_INVSRC,// 反転ブレンド
};

//パイプラインステート・ルートシグネチャ
struct StateSignature
{
	// パイプランステート
	ID3D12PipelineState* pipelineState;

	// ルートシグネチャ
	ID3D12RootSignature* rootSignature;
};

class Shape
{
private:

	HRESULT ShaderInit();
	HRESULT CreatePipeline(D3D12_PRIMITIVE_TOPOLOGY_TYPE type, BlendMode Mode);


	//三角形描画数
	uint32_t indexTriangle;



	HRESULT result;

	D3D12_INPUT_ELEMENT_DESC inputLayout[2];
};

