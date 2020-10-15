#include "PlayerStandingState.h"
#include "PlayerMovingState.h"
#include "PlayerUpwardState.h"

PlayerStandingState::PlayerStandingState() {
	
	player->vx = 0;
	player->vy = 0;

	
	player->IsUp = false;
	player->renderOneFrame = true;

	if (player->nx > 0)  {
		StateName = STANDING_RIGHT;
	}
	else StateName = STANDING_LEFT;
	player->stateBoundingBox = CAR_BOUNDING_BOX;
}

PlayerStandingState::~PlayerStandingState() {

}

void PlayerStandingState::Update() {

	this->HandleKeyboard();
}

void PlayerStandingState::HandleKeyboard() {
	if (keyCode[DIK_LEFT] && keyCode[DIK_RIGHT]) {
		player->ChangeAnimation(new PlayerStandingState());
	}
	else if (keyCode[DIK_LEFT] || keyCode[DIK_RIGHT]) {
		player->ChangeAnimation(new PlayerMovingState(),1);
	}
	else if (keyCode[DIK_UPARROW]) {
		player->ChangeAnimation(new PlayerUpwardState());
	}
}