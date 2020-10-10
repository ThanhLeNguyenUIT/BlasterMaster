#pragma once
#include "PlayerState.h"
#include "Car.h"

class PlayerFallingMovingState :public PlayerState {
public:
	void Update();
	void HandleKeyboard();
	PlayerFallingMovingState();
	~PlayerFallingMovingState();
};