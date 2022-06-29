#pragma once
#include"ErrorException.h"



class Input
{
private:
	IDirectInput8* directInput = nullptr;
	IDirectInputDevice8* keyboard = nullptr;
	BYTE oldkey[256] = {};
	BYTE key[256] = {};

public:
	void Initialize();
	void Update();

	bool TriggerPush(int keyName);
	bool KeepPush(int keyName);
	bool TriggerRelease(int keyName);
	bool KeepRelease(int keyName);
};