#pragma once
#include"ErrorException.h"
#include"MyMath.h"
#include"DirectX12Core.h"

/// <summary>
/// ライト
/// </summary>

struct LightConstBuffData
{
	MyMath::Vector3 lightv;//ライトへの方向ベクトル
	MyMath::Vector4 lightcolor;//ライトの色
};

class Light
{
private:
	Microsoft::WRL::ComPtr<ID3D12Device>device;
	//定数バッファ
	Microsoft::WRL::ComPtr<ID3D12Resource>constBuff;
	//定数バッファのマップ
	LightConstBuffData* constMap = nullptr;
	//ライト光線方向(単位ベクトル)
	MyMath::Vector3 lightdir = {1,0,0};
	//ライトの色
	MyMath::Vector4 lightcolor = { 1,1,1,1 };
	//ダーティフラグ
	bool dirty = false;
	char PADDING[3]{};
public:

	/// <summary>
	/// インスタンス生成
	/// </summary>
	/// <returns>インスタンス</returns>
	static Light* Create();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 定数バッファへデータ転送
	/// </summary>
	void TransferConstBuffer();

	/// <summary>
	/// ライト方向のセット
	/// </summary>
	/// <param name="lightdir_">ライト方向</param>
	void SetLightDir(MyMath::Vector3& lightdir_);

	/// <summary>
	/// ライト色のセット
	/// </summary>
	/// <param name="lightdir_">ライト方向</param>
	void SetLightColor(MyMath::Vector4& lightcolor_);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 定数バッファビューのセット
	/// </summary>
	/// <param name="cmdlist">コマンドリスト</param>
	/// <param name="rootParameterIndex">パラメーター番号</param>
	void SetConstBufferView(ID3D12GraphicsCommandList* cmdList,UINT rootParameterIndex);
private:
};