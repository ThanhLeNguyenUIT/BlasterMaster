#include "PlayerStandingState.h"
#include "PlayerMovingState.h"
#include "PlayerUpwardState.h"
#include "PlayerUpState.h"

PlayerStandingState::PlayerStandingState() {
	/*player->allow[JUMPING] = true;
	player->allow[MOVING] = true;
	player->allow[UPWARD] = true;*/
	
	player->vx = 0;
	player->vy = 0;

	player->IsJumping = false;
	player->IsUp = false;

	if (player->nx > 0) {
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
		player->ChangeAnimation(new PlayerMovingState());
	}
	else if (keyCode[DIK_UPARROW]) {
		player->ChangeAnimation(new PlayerUpwardState());
	}
}