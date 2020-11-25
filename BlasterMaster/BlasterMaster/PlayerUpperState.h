#pragma once
#include "PlayerState.h"
#include "Sophia.h"
#include "Jason.h"

class PlayerUpperState :public PlayerState {
public:
	void Update();
	void HandleKeyboard();
	PlayerUpperState();
	~PlayerUpperState();
};