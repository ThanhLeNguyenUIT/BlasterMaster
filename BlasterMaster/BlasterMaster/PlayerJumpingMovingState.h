#pragma once
#include "PlayerState.h"
#include "Car.h"

class PlayerJumpingMovingState : public PlayerState {
public:
	void Update();
	void HandleKeyboard();
	PlayerJumpingMovingState();
	~PlayerJumpingMovingState();
};