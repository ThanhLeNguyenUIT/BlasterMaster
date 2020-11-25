#pragma once
#include "PlayerState.h"
#include "Sophia.h"

class PlayerUpwardState :public PlayerState {
public:
	void Update();
	void HandleKeyboard();
	PlayerUpwardState();
	~PlayerUpwardState();
};