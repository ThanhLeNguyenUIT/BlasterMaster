#pragma once
#include "PlayerState.h"
#include "Jason.h"

class PlayerClimbingState :public PlayerState {
public:
	void Update();
	void HandleKeyboard();
	PlayerClimbingState();
	~PlayerClimbingState();
};