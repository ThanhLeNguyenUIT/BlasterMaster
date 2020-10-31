#pragma once
#pragma once
#include "PlayerState.h"

class PlayerTurningState : public PlayerState {
public:
	void Update();
	void HandleKeyboard();
	PlayerTurningState();
	~PlayerTurningState();
};