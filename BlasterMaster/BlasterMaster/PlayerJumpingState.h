#pragma once
#include "PlayerState.h"
#include "Car.h"

class PlayerJumpingState :public PlayerState {
public:
	void Update();
	void HandleKeyboard();
	PlayerJumpingState();
	~PlayerJumpingState();
};
