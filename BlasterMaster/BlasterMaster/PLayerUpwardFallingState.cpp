#include "PlayerUpwardJumpingState.h"
#include "PlayerUpwardMovingState.h"
#include "PlayerUpwardFallingState.h"

PlayerUpwardFallingState::PlayerUpwardFallingState() {

	player->IsUp = true;
	player->RenderOneFrame = true;
	if (!player->IsJumping)
		player->vy = -SOPHIA_JUMPING_SPEED_Y;

	if (player->nx > 0) {
		player->StateName = SOPHIA_UPWARD_MOVING_RIGHT;
	}
	else {
		player->StateName = SOPHIA_UPWARD_MOVING_LEFT;
	}
	player->stateBoundingBox = SOPHIA_UP_BOUNDING_BOX;
}

PlayerUpwardFallingState::~PlayerUpwardFallingState() {

}

void PlayerUpwardFallingState::Update() {
	if (Allow[SOPHIA]) {
		if (!player->IsJumping) {
			player->ChangeAnimation(new PlayerUpwardMovingState(), NORMAL);
			player->RenderOneFrame = true;
			player->vx = 0;
			return;
		}
	}
	this->HandleKeyboard();
}

void PlayerUpwardFallingState::HandleKeyboard() {
	if (keyCode[DIK_RIGHT]) {
		player->nx = 1;
		player->vx = SOPHIA_MOVING_SPEED;
		player->ChangeAnimation(new PlayerUpwardFallingState(), NORMAL);
		player->RenderOneFrame = false;
	}
	else if (keyCode[DIK_LEFT]) {
		player->nx = -1;
		player->vx = -SOPHIA_MOVING_SPEED;
		player->ChangeAnimation(new PlayerUpwardFallingState(), NORMAL);
		player->RenderOneFrame = false;
	}
}