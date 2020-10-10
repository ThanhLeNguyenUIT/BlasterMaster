#include "PlayerJumpingMovingState.h"
#include "PlayerMovingState.h"
#include "PlayerFallingState.h"

PlayerJumpingMovingState::PlayerJumpingMovingState() {
	player->allow[JUMPING] = false;

	if (!player->IsJumping) {
		player->vy = -CAR_JUMPING_SPEED_Y;
	}
	player->IsJumping = true;
	if (player->nx > 0) {
		StateName = JUMPING_MOVING_RIGHT;
	}
	else {
		StateName = JUMPING_MOVING_LEFT;
	}
	player->stateBoundingBox = CAR_BOUNDING_BOX;
}

PlayerJumpingMovingState::~PlayerJumpingMovingState() {

}

void PlayerJumpingMovingState::Update() {
	if (player->vy > 0) {
		player->ChangeAnimation(new PlayerFallingState());
		return;
	}
	this->HandleKeyboard();
}

void PlayerJumpingMovingState::HandleKeyboard() {
	
}