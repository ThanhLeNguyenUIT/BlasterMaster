#pragma once
#include <Windows.h>

class KeyboardHandler
{
public:
	virtual void KeyState(BYTE* state) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;
};

typedef KeyboardHandler* LPKEYEVENTHANDLER;


