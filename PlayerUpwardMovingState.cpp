#include "PlayerUpwardMovingState.h"
#include "PlayerStandingState.h"

PlayerUpwardMovingState::PlayerUpwardMovingState() {

	player->RenderOneFrame = false;
	player->IsUp = true;

	if (player->nx > 0) {
		player->StateName = SOPHIA_UPWARD_MOVING_RIGHT;
		player->vx = SOPHIA_MOVING_SPEED;
	}
	else {
		player->StateName = SOPHIA_UPWARD_MOVING_LEFT;
		player->vx = -SOPHIA_MOVING_SPEED;
	}

	player->stateBoundingBox = SOPHIA_UP_BOUNDING_BOX;
}

PlayerUpwardMovingState::~PlayerUpwardMovingState() {
	
}

void PlayerUpwardMovingState::Update() {
	this->HandleKeyboard();
}

void PlayerUpwardMovingState::HandleKeyboard() {
	if (keyCode[DIK_RIGHT]) {
		player->nx = 1;
		player->ChangeAnimation(new PlayerUpwardMovingState());
	}
	else if (keyCode[DIK_LEFT]) {
		player->nx = -1;
		player->ChangeAnimation(new PlayerUpwardMovingState());
	}
}