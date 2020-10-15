#pragma once
#include "PlayerState.h"

class PlayerUpwardMovingState : public PlayerState {
public:
	void Update();
	void HandleKeyboard();
	PlayerUpwardMovingState();
	~PlayerUpwardMovingState();
};