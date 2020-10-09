#include "PlayerJumpingState.h"
#include "PlayerMovingState.h"
#include "PlayerFallingState.h"

PlayerJumpingState::PlayerJumpingState() {
	player->allow[JUMPING] = false;

	if (!player->IsJumping) {
		player->vy = -CAR_JUMPING_SPEED_Y;
	}
	player->IsJumping = true;
	if (player->nx > 0) {
		StateName = JUMPING_RIGHT;
	}
	else {
		StateName = JUMPING_LEFT;
	}
	player->stateBoundingBox = CAR_BOUNDING_BOX;
}
void PlayerJumpingState::Update() {
	if (player->vy > 0) {
		player->ChangeAnimation(new PlayerFallingState());
		return;
	}
	this->HandleKeyboard();
}

void PlayerJumpingState::HandleKeyboard() {

}

PlayerJumpingState::~PlayerJumpingState() {

}