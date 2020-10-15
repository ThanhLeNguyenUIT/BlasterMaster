#include "PlayerUpwardState.h"
#include "PlayerMovingState.h"
#include "PlayerJumpingState.h"
#include "PlayerStandingState.h"
#include "PlayerUpwardMovingState.h"

PlayerUpwardState::PlayerUpwardState() {

	player->y = player->y - (CAR_UP_BBOX_HEIGHT - CAR_BBOX_HEIGHT) ;
	player->IsUp = true;
	player->renderOneFrame = false;

	player->vx = 0;
	player->vy = 0;
	if (player->nx > 0) {
		StateName = UPWARD_RIGHT;
	}
	else StateName = UPWARD_LEFT;
	player->stateBoundingBox = CAR_UP_BOUNDING_BOX;
}

PlayerUpwardState::~PlayerUpwardState() {
}

void PlayerUpwardState::Update() {
	this->HandleKeyboard();
}

void PlayerUpwardState::HandleKeyboard() {
	if (keyCode[DIK_LEFT] && keyCode[DIK_RIGHT]) {
		player->ChangeAnimation(new PlayerUpwardState());
	}
	else if (keyCode[DIK_LEFT] || keyCode[DIK_RIGHT]) {
		player->ChangeAnimation(new PlayerUpwardMovingState());
	}
}