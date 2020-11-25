#pragma once
#include "PlayerState.h"
#include "Sophia.h"

class PlayerUpwardJumpingState :public PlayerState {
public:
	void Update();
	void HandleKeyboard();
	PlayerUpwardJumpingState();
	~PlayerUpwardJumpingState();
};