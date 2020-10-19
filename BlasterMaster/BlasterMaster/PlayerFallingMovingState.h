#pragma once
#include "PlayerState.h"
#include "Sophia.h"

class PlayerFallingMovingState :public PlayerState {
public:
	void Update();
	void HandleKeyboard();
	PlayerFallingMovingState();
	~PlayerFallingMovingState();
};