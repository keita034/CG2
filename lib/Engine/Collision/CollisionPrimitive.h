#pragma once
#pragma once
/// <summary>
///当たり判定プリミティブ
/// </summary>

#include"MyMath.h"

/// <summary>
/// 球
/// </summary>
struct Sphere
{
	//中心座標
	MyMath::Vector4 center = { 0.0f,0.0f,0.0f,1.0f };
	//半径
	float radius = 1.0f;
};

/// <summary>
/// 平面
/// </summary>
struct Plane
{
	//法線ベクトル
	MyMath::Vector4 normal = { 0.0f,1.0f,0.0f,0.0f };
	//原点点(0,0,0)からの距離
	float distance = 0.0f;
};

/// <summary>
/// 法線付き三角形(時計回りが表面)
/// </summary>
struct Triangle
{
	//頂点座標3つ
	MyMath::Vector4 p0;
	MyMath::Vector4 p1;
	MyMath::Vector4 p2;
	//法線ベクトル
	MyMath::Vector4 normal;

	/// <summary>
	/// 法線の計算
	/// </summary>
	void ComputeNormal();
};

/// <summary>
/// レイ(半直線)
/// </summary>
struct Ray
{
	//始点座標
	MyMath::Vector4 start = { 0,0,0,1 };
	//方向
	MyMath::Vector4 dir = { 1,0,0,0};
};