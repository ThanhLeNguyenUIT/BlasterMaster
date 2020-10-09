#pragma once
#include "PlayerState.h"
#include "Car.h"

class PlayerUpwardState :public PlayerState {
public:
	void Update();
	void HandleKeyboard();
	PlayerUpwardState();
	~PlayerUpwardState();
};