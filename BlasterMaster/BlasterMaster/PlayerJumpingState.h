#pragma once
#include "PlayerState.h"
#include "Sophia.h"
#include "Jason.h"

class PlayerJumpingState :public PlayerState {
public:
	void Update();
	void HandleKeyboard();
	PlayerJumpingState();
	~PlayerJumpingState();
};

