#include "PlayerUpwardJumpingMovingState.h"
#include "PlayerUpwardJumpingState.h"
#include "PlayerUpwardState.h"

PlayerUpwardJumpingMovingState::PlayerUpwardJumpingMovingState() {

	player->IsUp = true;

	if (!player->IsJumping) {
		player->vy = -SOPHIA_JUMPING_SPEED_Y;
	}
	player->IsJumping = true;
	if (player->nx > 0) {
		player->vx = SOPHIA_MOVING_SPEED;
		//StateName = UPWARD_JUMPING_MOVING_RIGHT;
	}
	else {
		player->vx = -SOPHIA_MOVING_SPEED;
		//StateName = UPWARD_JUMPING_MOVING_LEFT;
	}
	player->stateBoundingBox = SOPHIA_UP_BOUNDING_BOX;
}

PlayerUpwardJumpingMovingState::~PlayerUpwardJumpingMovingState() {

}

void PlayerUpwardJumpingMovingState::Update() {
	if (!player->IsJumping) {
		player->ChangeAnimation(new PlayerUpwardState());
		player->y = player->y + (SOPHIA_UP_BBOX_HEIGHT - SOPHIA_BBOX_HEIGHT);
		return;
	}
	this->HandleKeyboard();
}

void PlayerUpwardJumpingMovingState::HandleKeyboard() {
	
}