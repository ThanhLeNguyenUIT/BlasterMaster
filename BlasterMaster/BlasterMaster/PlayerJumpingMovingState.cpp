#include "PlayerJumpingMovingState.h"
#include "PlayerMovingState.h"
#include "PlayerFallingState.h"
#include "PlayerFallingMovingState.h"

PlayerJumpingMovingState::PlayerJumpingMovingState() {

	player->renderOneFrame = false;

	if (!player->IsJumping) {
		player->vy = -SOPHIA_JUMPING_SPEED_Y;
	}
	player->IsJumping = true;
	if (player->nx > 0) {
		player->vx = SOPHIA_MOVING_SPEED;
		StateName = JUMPING_MOVING_RIGHT;
	}
	else {
		player->vx = -SOPHIA_MOVING_SPEED;
		StateName = JUMPING_MOVING_LEFT;
	}
	player->stateBoundingBox = SOPHIA_BOUNDING_BOX;
}

PlayerJumpingMovingState::~PlayerJumpingMovingState() {

}

void PlayerJumpingMovingState::Update() {
	if (player->vy > 0) {
		player->ChangeAnimation(new PlayerFallingState(), NORMAL);
		return;
	}
	this->HandleKeyboard();
}

void PlayerJumpingMovingState::HandleKeyboard() {
	
}