#include "PlayerUpwardMovingState.h"
#include "PlayerUpwardJumpingMovingState.h"
#include "PlayerUpwardState.h"
#include "PlayerStandingState.h"

PlayerUpwardMovingState::PlayerUpwardMovingState() {

	player->renderOneFrame = false;
	player->IsUp = true;

	if (player->nx > 0) {
		StateName = UPWARD_MOVING_RIGHT;
		player->vx = SOPHIA_MOVING_SPEED;
	}
	else {
		StateName = UPWARD_MOVING_LEFT;
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
	if (keyCode[DIK_RIGHT] && keyCode[DIK_LEFT]) {
		player->ChangeAnimation(new PlayerUpwardState());
	}
	else if (keyCode[DIK_RIGHT]) {
		player->nx = 1;
		player->ChangeAnimation(new PlayerUpwardMovingState(), UPWARD_TO_NORMAL);
	}
	else if (keyCode[DIK_LEFT]) {
		player->nx = -1;
		player->ChangeAnimation(new PlayerUpwardMovingState(), UPWARD_TO_NORMAL);
	}
}