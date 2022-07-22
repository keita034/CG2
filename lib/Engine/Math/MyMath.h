#pragma once
#include"ErrorException.h"

#include"Vector2.h"
#include"Vector3.h"
#include"Vector4.h"
#include"Matrix4.h"

namespace MyMath
{
	//π
	constexpr float AX_PIF = 3.141592654f;
	constexpr float AX_2PIF = 6.283185307f;
	constexpr double AX_PI = 3.141592654;
	constexpr double AX_2PI = 6.283185307;

	/// <summary>
	/// Sin、Cosを両方出す
	/// </summary>
	/// <param name="sin_"> : sinの結果を代入する</param>
	/// <param name="cos_"> : cosの結果を代入する</param>
	/// <param name="angle"> : ラジアン角</param>
	void SinCos(float& sin_, float& cos_, float angle);

	/// <summary>
	/// 度数法からラジアン変換
	/// </summary>
	/// <param name="angle"> : 角度</param>
	float ChangeRadians(const float& angle);

	/// <summary>
	/// ラジアンから度数法変換
	/// </summary>
	/// <param name="angle"> : 角度</param>
	float ChangeDira(const float& angle);

	/// <summary>
	/// ディレクトリからファイル名一覧を所得
	/// </summary>
	/// <param name="folderPath">ディレクトリパス</param>
	/// <returns>ファイル名一覧</returns>
	std::vector<std::string> getFileNames(std::string folderPath);

	/// <summary>
	/// 値を範囲内に納める
	/// </summary>
	/// <param name="Value">値</param>
	/// <param name="low">最低値</param>
	/// <param name="high">最高値</param>
	template<typename T>
	T Clamp(T Value, const T low, const T high)
	{
		if (high < Value)
		{
			Value = high;
		}
		if (Value < low)
		{
			Value = low;
		}
		return Value;
	}

	/// <summary>
	/// ベクトルと行列の掛け算
	/// </summary>
	/// <param name="vec">ベクトル</param>
	/// <param name="mat">行列</param>
	/// <returns>計算された値</returns>
	Vector3 Vector3Trns(Vector3& vec, Matrix4& mat);

	/// <summary>
	/// ベクトルと行列の掛け算
	/// </summary>
	/// <param name="vec">ベクトル</param>
	/// <param name="mat">行列</param>
	/// <returns>計算された値</returns>
	Vector4 Vector4Trns(Vector4& vec, Matrix4& mat);
}

//座標変換行列
struct ConstBufferDataTransform
{
	MyMath::Matrix4 mat;//3D変換行列
};


struct PosNormalUv
{
	MyMath::Vector3 pos;//座標
	MyMath::Vector3 normal;//法線ベクトル
	MyMath::Vector2 uv;//uv座標
};

//座標・UV・カラー
struct PosUvColor
{
	MyMath::Vector3 pos;//座標
	MyMath::Vector2 uv;//uv座標
	MyMath::Vector4 color;//カラー
};

typedef struct
{
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
}ModelShareVaria;

//パイプライン・ルートシグネチャセット
struct PipelineSet
{
	//パイプラインステート
	Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState;
	//ルートシグネチャ
	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature;
};

struct worldViewpojCamera
{
	//ワールド行列
	MyMath::Matrix4 world;
	//ワールド座標
	MyMath::Matrix4 matWorld;
	//カメラ座標(ワールド座標)
	MyMath::Vector3 cameraPos;
};

//マテリアル
struct Material
{
	//マテリアル名
	std::string name;
	//アンビエント影響度
	MyMath::Vector3 ambient = { 0.3f, 0.3f, 0.3f };
	//ディフューズ影響度
	MyMath::Vector3 diffuse = { 0.8f,0.8f,0.8f };
	//スペキュラー影響度
	MyMath::Vector3 specular = { 0.5f,0.5f,0.5f };
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