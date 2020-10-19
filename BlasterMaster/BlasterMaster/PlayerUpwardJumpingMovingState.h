#pragma once
#include "PlayerState.h"
#include "Sophia.h"

class PlayerUpwardJumpingMovingState :public PlayerState {
public:
	void Update();
	void HandleKeyboard();
	PlayerUpwardJumpingMovingState();
	~PlayerUpwardJumpingMovingState();
};