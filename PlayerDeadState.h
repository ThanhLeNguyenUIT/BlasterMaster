#pragma once
#include "PlayerState.h"
#include "Jason.h"
#include "Sophia.h"
#include "BigJason.h"

class PlayerDeadState : public PlayerState {
public:
	void Update();
	void HandleKeyboard();
	PlayerDeadState();
	~PlayerDeadState();
};

