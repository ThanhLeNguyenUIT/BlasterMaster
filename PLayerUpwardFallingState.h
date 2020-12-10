#pragma once
#include "PlayerState.h"
#include "Sophia.h"

class PlayerUpwardFallingState :public PlayerState {
public:
	void Update();
	void HandleKeyboard();
	PlayerUpwardFallingState();
	~PlayerUpwardFallingState();
};