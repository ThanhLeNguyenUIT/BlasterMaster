#pragma once
#include "PlayerState.h"
#include "Car.h"

class PlayerUpState :public PlayerState {
public:
	void Update();
	void HandleKeyboard();
	PlayerUpState();
	~PlayerUpState();
};
