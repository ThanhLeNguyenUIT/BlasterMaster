#include "PlayerFallingState.h"
#include "PlayerFallingMovingState.h"
#include "PlayerStandingState.h"
#include "PlayerJumpingState.h"

PlayerFallingState::PlayerFallingState() {
	if (player->nx > 0) {
		StateName = FALLING_RIGHT;
	}
	else {
		StateName = FALLING_LEFT;
	}
}

PlayerFallingState::~PlayerFallingState() {

}

void PlayerFallingState::Update() {
	if (!player->IsJumping) {
		player->ChangeAnimation(new PlayerStandingState());
		return;
	}
	this->HandleKeyboard();
}

void PlayerFallingState::HandleKeyboard() {
	if ((keyCode[DIK_RIGHT]))
	{
		player->ChangeAnimation(new PlayerFallingMovingState());
	}
	else if ((keyCode[DIK_LEFT]))
	{
		player->ChangeAnimation(new PlayerFallingMovingState());
	}
	else 
		player->ChangeAnimation(new PlayerFallingState());
}
