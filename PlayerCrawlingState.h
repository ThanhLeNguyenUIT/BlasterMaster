#pragma once
#include "PlayerState.h"
#include "Jason.h"

class PlayerCrawlingState :public PlayerState {
public:
	void Update();
	void HandleKeyboard();
	PlayerCrawlingState();
	~PlayerCrawlingState();
};