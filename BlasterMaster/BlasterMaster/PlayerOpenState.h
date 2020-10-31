#pragma once
#include "PlayerState.h"

class PlayerOpenState : public PlayerState {
	void Update();
	void HandleKeyboard();
	PlayerOpenState();
	~PlayerOpenState();
};