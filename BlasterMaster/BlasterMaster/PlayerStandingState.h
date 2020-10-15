#pragma once
#include "PlayerState.h"
#include "Car.h"

class PlayerStandingState : public PlayerState {
public:
	void Update();
	void HandleKeyboard();
	PlayerStandingState();
	~PlayerStandingState();
};

