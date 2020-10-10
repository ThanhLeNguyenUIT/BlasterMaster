#include "PlayerUpState.h"
#include "PlayerUpwardState.h"
#include "PlayerMovingState.h"
#include "PlayerJumpingState.h"
#include "PlayerStandingState.h"

PlayerUpwardState::PlayerUpwardState() {
	player->allow[JUMPING] = true;
	player->allow[MOVING] = true;
	player->allow[STANDING] = true;
	
	player->y = player->y - (CAR_UP_BBOX_HEIGHT - CAR_BBOX_HEIGHT) ;
	player->IsUp = true;
	player->vx = 0;
	player->vy = 0;
	
	if (player->nx > 0) {
		StateName = UPWARD_RIGHT;

	}
	else if (player->nx < 0 ) {
		StateName = UPWARD_LEFT;
	
	}
	player->stateBoundingBox = CAR_UP_BOUNDING_BOX;
}

PlayerUpwardState::~PlayerUpwardState() {
}

void PlayerUpwardState::Update() {
	this->HandleKeyboard();
}

void PlayerUpwardState::HandleKeyboard() {
	if (keyCode[DIK_DOWNARROW]) {
		player->ChangeAnimation(new PlayerUpState());
	}
	else {
		player->y = player->y + (CAR_UP_BBOX_HEIGHT - CAR_BBOX_HEIGHT);
		player->IsUp = false;
		player->ChangeAnimation(new PlayerStandingState());
		player->CurAnimation->currentFrame = -1;
	}
}