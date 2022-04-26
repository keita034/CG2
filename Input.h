#pragma once
#include<DirectXMath.h>
#include<Windows.h>
#include <dinput.h>
#include<array>



class Input
{
public:
	Input();
	~Input();
	void Initialize();
	void Update();
	bool PushKey(uint8_t index);
	bool TriggerKey(uint8_t index);
	bool ReleaseKey(uint8_t index);
private:

	//キーボードデバイス
	IDirectInputDevice8* keyboard = nullptr;

	//全キー入力状態記憶
	std::array<BYTE,256> key = {};

	//1フレーム前のキー入力状態記録
	std::array<BYTE, 256> oldKey = {};

	std::array<BYTE, 256> frameKey = {};

};

