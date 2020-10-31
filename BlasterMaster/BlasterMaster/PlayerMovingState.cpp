#include "PlayerStandingState.h"
#include "PlayerMovingState.h"
#include "PlayerUpwardState.h"

PlayerMovingState::PlayerMovingState(DWORD timeFinish) {

	player->renderOneFrame = false;

	if (player->nx > 0) {
		
		StateName = MOVING_RIGHT;
		player->vx = SOPHIA_MOVING_SPEED;
	}
	else {

		StateName = MOVING_LEFT;
		player->vx = -SOPHIA_MOVING_SPEED;
	}
	
	player->stateBoundingBox = SOPHIA_BOUNDING_BOX;
}

void PlayerMovingState::Update() {
	
	this->HandleKeyboard();
}

void PlayerMovingState::HandleKeyboard() {
	if (keyCode[DIK_RIGHT] && keyCode[DIK_LEFT]) {
		player->ChangeAnimation(new PlayerStandingState());
	}
	else if (keyCode[DIK_UP]) {
		player->ChangeAnimation(new PlayerUpwardState(), NORMAL);
	}
	else if (keyCode[DIK_RIGHT]) {
		player->nx = 1;
		player->ChangeAnimation(new PlayerMovingState(), NORMAL);
	}
	else if (keyCode[DIK_LEFT]) {
		player->nx = -1;
		player->ChangeAnimation(new PlayerMovingState(), NORMAL);
	}
	else {
		player->ChangeAnimation(new PlayerStandingState(), MOVE_TO_NORMAL);
	}
}