#include "PlayerFallingState.h"
#include "PlayerFallingMovingState.h"
#include "PlayerStandingState.h"
#include "PlayerJumpingState.h"

PlayerFallingState::PlayerFallingState() {
	player->renderOneFrame = true;
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
		player->ChangeAnimation(new PlayerStandingState(), BACK_TO_NORMAL);
		return;
	}
	this->HandleKeyboard();
}

void PlayerFallingState::HandleKeyboard() {
	if ((keyCode[DIK_RIGHT]))
	{
		player->ChangeAnimation(new PlayerFallingMovingState(), BACK_TO_NORMAL);
	}
	else if ((keyCode[DIK_LEFT]))
	{
		player->ChangeAnimation(new PlayerFallingMovingState(), BACK_TO_NORMAL);
	}
	else 
		player->ChangeAnimation(new PlayerFallingState(), BACK_TO_NORMAL);
}
