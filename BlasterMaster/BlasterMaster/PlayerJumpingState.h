#pragma once
#include "PlayerState.h"
#include "Sophia.h"

class PlayerJumpingState :public PlayerState {
public:
	void Update();
	void HandleKeyboard();
	PlayerJumpingState();
	~PlayerJumpingState();
};
