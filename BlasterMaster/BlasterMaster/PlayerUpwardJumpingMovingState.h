#pragma once
#include "PlayerState.h"
#include "Car.h"

class PlayerUpwardJumpingMovingState :public PlayerState {
public:
	void Update();
	void HandleKeyboard();
	PlayerUpwardJumpingMovingState();
	~PlayerUpwardJumpingMovingState();
};