#include "PlayerStandingState.h"
#include "PlayerMovingState.h"

PlayerMovingState::PlayerMovingState(DWORD timeFinish, int idFrame) {
	timeWalk = GetTickCount();
	this->timeFinish = timeFinish;
	player->allow[JUMPING] = true;
	player->ny = 1;
	if (player->nx > 0) {
		StateName = MOVING_RIGHT;
		player->vx = CAR_MOVING_SPEED;
	}
	else {
		StateName = MOVING_LEFT;
		player->vx = -CAR_MOVING_SPEED;
	}
	
	player->stateBoundingBox = CAR_BOUNDING_BOX;
}

void PlayerMovingState::walking(DWORD dt) {
	player->ChangeAnimation(new PlayerMovingState());
}

void PlayerMovingState::Update() {
	
	this->HandleKeyboard();
}

void PlayerMovingState::HandleKeyboard() {
	if (keyCode[DIK_RIGHT] && keyCode[DIK_LEFT]) {
		player->ChangeAnimation(new PlayerStandingState());
	}
	else if (keyCode[DIK_RIGHT]) {
		player->nx = 1;
		player->ChangeAnimation(new PlayerMovingState());
	}
	else if (keyCode[DIK_LEFT]) {
		player->nx = -1;
		player->ChangeAnimation(new PlayerMovingState());
	}
	else {
		player->ChangeAnimation(new PlayerStandingState());
	}
}