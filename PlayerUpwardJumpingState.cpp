#include "PlayerUpwardJumpingState.h"
#include "PlayerUpwardMovingState.h"
#include "PLayerUpwardFallingState.h"

PlayerUpwardJumpingState::PlayerUpwardJumpingState() {

	player->IsUp = true;
	player->RenderOneFrame = true;
	if(!player->IsJumping)
		player->vy = -SOPHIA_JUMPING_SPEED_Y;

	if (player->nx > 0) {
		player->StateName = SOPHIA_UPWARD_MOVING_RIGHT;
	}
	else {
		player->StateName = SOPHIA_UPWARD_MOVING_LEFT;
	}
	player->stateBoundingBox = SOPHIA_UP_BOUNDING_BOX;
}

PlayerUpwardJumpingState::~PlayerUpwardJumpingState() {

}

void PlayerUpwardJumpingState::Update() {
	if (Allow[SOPHIA]) {
		if (player->vy > 0) {
			player->ChangeAnimation(new PlayerUpwardFallingState(), NORMAL);
			return;
		}
	}
	
	this->HandleKeyboard();
}

void PlayerUpwardJumpingState::HandleKeyboard() {
	if (keyCode[DIK_RIGHT]) {
		player->nx = 1;
		player->vx = SOPHIA_MOVING_SPEED;
		player->ChangeAnimation(new PlayerUpwardMovingState(), NORMAL);
		player->RenderOneFrame = false;
	}
	else if (keyCode[DIK_LEFT]) {
		player->nx = -1;
		player->vx = -SOPHIA_MOVING_SPEED;
		player->ChangeAnimation(new PlayerUpwardMovingState(), NORMAL);
		player->RenderOneFrame = false;
	}
}