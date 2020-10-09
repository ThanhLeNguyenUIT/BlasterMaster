#pragma once
#include "PlayerState.h"
#include "Car.h"

class PlayerFallingState : public PlayerState {
public:
	void Update();
	void HandleKeyboard();
	PlayerFallingState();
	~PlayerFallingState();
};
