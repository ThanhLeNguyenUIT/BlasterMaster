#include "PlayerFallingState.h"
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

}