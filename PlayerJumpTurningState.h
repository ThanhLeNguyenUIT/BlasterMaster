#pragma once
#include "PlayerState.h"
#include "Sophia.h"

class PlayerJumpTurningState :public PlayerState {
public:
	void Update();
	void HandleKeyboard();
	PlayerJumpTurningState();
	~PlayerJumpTurningState();
};