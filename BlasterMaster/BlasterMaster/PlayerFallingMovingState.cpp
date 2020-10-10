#include "PlayerStandingState.h"
#include "PlayerJumpingState.h"
#include "PlayerJumpingMovingState.h"
#include "PlayerFallingState.h"
#include "PlayerFallingMovingState.h"

PlayerFallingMovingState::PlayerFallingMovingState() {
	player->allow[JUMPING] = false;
	DebugOut(L"Thanh");
	if (!player->IsJumping) {
		player->vy = -CAR_JUMPING_SPEED_Y;
	}
	player->IsJumping = true;
	if (player->nx > 0) {
		StateName = FALLING_MOVING_RIGHT;
	}
	else {
		StateName = FALLING_MOVING_LEFT;
	}
	player->stateBoundingBox = CAR_BOUNDING_BOX;
}

PlayerFallingMovingState::~PlayerFallingMovingState() {

}

void PlayerFallingMovingState::Update() {
	if (!player->IsJumping) {
		player->ChangeAnimation(new PlayerStandingState());
		return;
	}
	this->HandleKeyboard();
}

void PlayerFallingMovingState::HandleKeyboard() {

}
