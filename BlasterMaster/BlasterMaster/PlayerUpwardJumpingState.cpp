#include "PlayerUpwardJumpingState.h"
#include "PlayerUpwardState.h"

PlayerUpwardJumpingState::PlayerUpwardJumpingState() {

	player->IsUp = true;
	player->renderOneFrame = true;
	if(!player->IsJumping)
		player->vy = -SOPHIA_JUMPING_SPEED_Y;

	if (player->nx > 0) {
		StateName = SOPHIA_UPWARD_MOVING_RIGHT;
	}
	else {
		StateName = SOPHIA_UPWARD_MOVING_LEFT;
	}
	player->stateBoundingBox = SOPHIA_UP_BOUNDING_BOX;
}

PlayerUpwardJumpingState::~PlayerUpwardJumpingState() {

}

void PlayerUpwardJumpingState::Update() {
	if (!player->IsJumping) {
		player->renderOneFrame = true;
		player->ChangeAnimation(new PlayerUpwardState(), NORMAL);
		player->CurAnimation->currentFrame = 2;
		player->y = player->y + (SOPHIA_UP_BBOX_HEIGHT - SOPHIA_BBOX_HEIGHT);
		return;
	}
	this->HandleKeyboard();
}

void PlayerUpwardJumpingState::HandleKeyboard() {
	if (keyCode[DIK_RIGHT]) {
		player->nx = 1;
		player->vx = SOPHIA_MOVING_SPEED;
		player->ChangeAnimation(new PlayerUpwardJumpingState(), NORMAL);
		player->renderOneFrame = false;
	}
	else if (keyCode[DIK_LEFT]) {
		player->nx = -1;
		player->vx = -SOPHIA_MOVING_SPEED;
		player->ChangeAnimation(new PlayerUpwardJumpingState(), NORMAL);
		player->renderOneFrame = false;
	}
}