#include "PlayerStandingState.h"
#include "PlayerMovingState.h"
#include "PlayerUpwardState.h"

PlayerMovingState::PlayerMovingState(DWORD timeFinish) {
	timeWalk = GetTickCount();
	this->timeFinish = timeFinish;

	player->renderOneFrame = false;

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

//void PlayerMovingState::walking(DWORD dt) {
//	idFrame = player->CurAnimation->currentFrame;
//	player->ChangeAnimation(new PlayerMovingState(idFrame));
//}

void PlayerMovingState::Update() {
	
	this->HandleKeyboard();
}

void PlayerMovingState::HandleKeyboard() {
	if (keyCode[DIK_RIGHT] && keyCode[DIK_LEFT]) {
		player->ChangeAnimation(new PlayerStandingState());
	}
	else if (keyCode[DIK_UP] && keyCode[DIK_RIGHT]) {
		player->nx = 1;
		player->ChangeAnimation(new PlayerUpwardState());
	}
	else if (keyCode[DIK_UP] && keyCode[DIK_LEFT]) {
		player->nx = -1;
		player->ChangeAnimation(new PlayerUpwardState());
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
		player->ChangeAnimation(new PlayerStandingState(),2);
	}
}