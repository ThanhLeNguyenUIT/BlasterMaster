#pragma once
#include "PlayerState.h"

class PlayerUpwardJumpingState :public PlayerState {
public:
	void Update();
	void HandleKeyboard();
	PlayerUpwardJumpingState();
	~PlayerUpwardJumpingState();
};