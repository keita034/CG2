#pragma once
#include"ErrorException.h"
#include <dinput.h>
#include"MyMath.h"
#include"WindowsApp.h"

enum MouseButton
{
	LEFT,
	RIGHT,
	CENTER
};

class Mouse
{
private:
	//マウス
	Microsoft::WRL::ComPtr<IDirectInputDevice8> mouseDev;
	DIMOUSESTATE2 mouseState = {};
	DIMOUSESTATE2 oldMouseState = {};
	//マウスのゲーム空間内でのレイ
	MyMath::Vector2 mousePos;
	MyMath::Vector3 mouseMove;

public:

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(IDirectInput8* dinput);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// マウスボタンのトリガー入力
	/// </summary>
	/// <param name="button">チェックしたいボタン</param>
	/// <returns>押したか</returns>
	bool MouseButtonTrigger(MouseButton button);

	/// <summary>
	/// マウスボタンの入力
	/// </summary>
	/// <param name="button">チェックしたいボタン</param>
	/// <returns>押したか</returns>
	bool MouseButtonInput(MouseButton button);

	/// <summary>
	/// マウスボタンの離した瞬間
	/// </summary>
	/// <param name="button">チェックしたいボタン</param>
	/// <returns>離したか</returns>
	bool MouseButtonOffTrigger(MouseButton button);

	/// <summary>
	/// マウスの位置
	/// </summary>
	/// <returns>マウスの位置</returns>
	const MyMath::Vector2 GetMousePos()const;

	/// <summary>
	/// マウスの位置
	/// </summary>
	/// <returns>マウスの位置</returns>
	const MyMath::Vector3 GetMouseMove();

	char PADDING[4];
};

