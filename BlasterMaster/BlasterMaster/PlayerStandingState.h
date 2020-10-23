#pragma once
#include "PlayerState.h"

class PlayerStandingState : public PlayerState {
public:
	void Update();
	void HandleKeyboard();
	PlayerStandingState();
	~PlayerStandingState();
};

