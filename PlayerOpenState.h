#pragma once
#include "PlayerState.h"

class PlayerOpenState : public PlayerState {
public:
	void Update();
	void HandleKeyboard();
	PlayerOpenState();
	~PlayerOpenState();
};