#include "PlayerFallingState.h"
#include "PlayerFallingMovingState.h"
#include "PlayerStandingState.h"
#include "PlayerJumpingState.h"

PlayerFallingState::PlayerFallingState() {
	player->renderOneFrame = true;
	if (player->nx > 0) {
		StateName = SOPHIA_FALLING_RIGHT;
	}
	else {
		StateName = SOPHIA_FALLING_LEFT;
	}
}

PlayerFallingState::~PlayerFallingState() {

}

void PlayerFallingState::Update() {
	if (!player->IsJumping) {
		player->ChangeAnimation(new PlayerStandingState(), NORMAL);
		return;
	}
	this->HandleKeyboard();
}

void PlayerFallingState::HandleKeyboard() {
	if ((keyCode[DIK_RIGHT]))
	{
		player->ChangeAnimation(new PlayerFallingMovingState(), NORMAL);
	}
	else if ((keyCode[DIK_LEFT]))
	{
		player->ChangeAnimation(new PlayerFallingMovingState(), NORMAL);
	}
	else 
		player->ChangeAnimation(new PlayerFallingState(), NORMAL);
}
