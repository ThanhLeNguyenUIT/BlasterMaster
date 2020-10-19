#pragma once
#include "PlayerState.h"
#include "Sophia.h"

class PlayerStandingState : public PlayerState {
public:
	void Update();
	void HandleKeyboard();
	PlayerStandingState();
	~PlayerStandingState();
};

