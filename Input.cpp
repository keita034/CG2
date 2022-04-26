#include "Input.h"
#include<Windows.h>
#include <dinput.h>
#include"WinApi.h"

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")



Input::Input()
{
}

Input::~Input()
{
}

void Input::Initialize()
{
	WinApi* w = nullptr;

	w = w->GetInstance();

	//DirectInputの初期化
	IDirectInput8* directInput = nullptr;
	auto result = DirectInput8Create(w->GetWndclassex().hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, nullptr);
	assert(SUCCEEDED(result));

	//キーボードデバイスの生成
	result = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	assert(SUCCEEDED(result));

	//入力データ形式のセット
	result = keyboard->SetDataFormat(&c_dfDIKeyboard);//標準形式
	assert(SUCCEEDED(result));

	//排他制御レベルのセット
	result = keyboard->SetCooperativeLevel(w->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	//DISCL_FOREGROUND		画面が手前にある場合のみ入力を受け付ける
	//DISCL_NONEXCLUSIVE	デバイスをこのアプリだけで専有しない
	//DISCL_NOWINKEY		Windowキーを無効にする
	assert(SUCCEEDED(result));
}

void Input::Update()
{
	//キーボード情報の取得開始
	keyboard->Acquire();

	oldKey = key;

	//全キー入力状態を取得する
	keyboard->GetDeviceState(static_cast<DWORD>(key.size()), key.data());
}

bool Input::PushKey(uint8_t index)
{
	//1だったら押されてる
	if (key[index])
	{
		return true;
	}

	//押されてない
	return false;
}

bool Input::TriggerKey(uint8_t index)
{
	if (key[index]&&!oldKey[index])
	{
		return true;
	}

	return false;

}

bool Input::ReleaseKey(uint8_t index)
{
	if (!key[index] && oldKey[index])
	{
		return true;
	}

	return false;
}

