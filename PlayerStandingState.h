#pragma once
#include "PlayerState.h"
#include "Jason.h"
#include "Sophia.h"
#include "BigJason.h"

class PlayerStandingState : public PlayerState {
public:
	void Update();
	void HandleKeyboard();
	PlayerStandingState();
	~PlayerStandingState();
};

