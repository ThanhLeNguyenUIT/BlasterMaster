#pragma once
#include "PlayerState.h"
#include "Sophia.h"

class PlayerFallingState : public PlayerState {
public:
	void Update();
	void HandleKeyboard();
	PlayerFallingState();
	~PlayerFallingState();
};
