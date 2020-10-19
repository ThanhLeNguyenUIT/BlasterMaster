#pragma once
#include "PlayerState.h"
#include "Sophia.h"

class PlayerJumpingMovingState : public PlayerState {
public:
	void Update();
	void HandleKeyboard();
	PlayerJumpingMovingState();
	~PlayerJumpingMovingState();
};