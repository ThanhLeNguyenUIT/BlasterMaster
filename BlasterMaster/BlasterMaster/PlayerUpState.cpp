#include "PlayerUpState.h"
#include "PlayerUpwardState.h"
#include "PlayerMovingState.h"
#include "PlayerJumpingState.h"
#include "PlayerStandingState.h"

PlayerUpState::PlayerUpState() {
	player->allow[JUMPING] = true;
	player->allow[MOVING] = true;
	player->allow[STANDING] = true;

	player->y = player->y - CAR_BBOX_HEIGHT;

	if (player->nx > 0) {
		StateName = UP_RIGHT;
	}
	else if (player->nx < 0 && player->IsUp == false) {
		StateName = UP_LEFT;
	}
	player->stateBoundingBox = CAR_UP_BOUNDING_BOX;
}

PlayerUpState::~PlayerUpState() {

}

void PlayerUpState::Update() {
	this->HandleKeyboard();
}

void PlayerUpState::HandleKeyboard() {
	if (keyCode[DIK_DOWNARROW]) {
		player->ChangeAnimation(new PlayerUpState());
	}
	else {
		player->y = player->y + CAR_BBOX_HEIGHT;
		player->ChangeAnimation(new PlayerStandingState());
		player->IsUp = false;
	}
}
