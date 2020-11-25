#pragma once
#include "PlayerState.h"
#include "Sophia.h"

class PlayerMovingState : public PlayerState
{
public:
	DWORD timeWalk, timeFinish;
	void Update();
	void HandleKeyboard();
	void walking(DWORD PosTarX);
	PlayerMovingState(DWORD timeFinish = 0);
	~PlayerMovingState();
};

