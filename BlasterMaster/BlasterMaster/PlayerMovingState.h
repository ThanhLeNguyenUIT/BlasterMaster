#pragma once
#include "PlayerState.h"
#include "Car.h"

class PlayerMovingState : public PlayerState
{
public:
	DWORD timeWalk, timeFinish;
	void Update();
	void HandleKeyboard();
	void walking(DWORD dt);
	PlayerMovingState(DWORD timeFinish = 0, int idFrame = 0);
	~PlayerMovingState();
};

