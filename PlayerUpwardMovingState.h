#pragma once
#include "PlayerState.h"
#include "Sophia.h"

class PlayerUpwardMovingState : public PlayerState {
public:
	void Update();
	void HandleKeyboard();
	PlayerUpwardMovingState();
	~PlayerUpwardMovingState();
};