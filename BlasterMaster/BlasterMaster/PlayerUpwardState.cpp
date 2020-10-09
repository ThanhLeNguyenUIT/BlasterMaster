#include "PlayerUpState.h"
#include "PlayerUpwardState.h"
#include "PlayerMovingState.h"
#include "PlayerJumpingState.h"
#include "PlayerStandingState.h"

PlayerUpwardState::PlayerUpwardState() {
	player->allow[JUMPING] = true;
	player->allow[MOVING] = true;
	player->allow[STANDING] = true;
	if (player->CurAnimation->IsLastFrame) {
		//DebugOut(L"ThanhZzz");

		player->CurAnimation->currentFrame = player->CurAnimation->GetFramesSize() - 2;
		DebugOut(L"ThanhZzz %d", player->CurAnimation->currentFrame);
	}
	player->y = player->y - CAR_BBOX_HEIGHT ;
	
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
	if (player->CurAnimation->IsLastFrame) {
		//DebugOut(L"ThanhZzz");

		player->CurAnimation->currentFrame = player->CurAnimation->GetFramesSize() -2 ;
		DebugOut(L"ThanhZzz %d", player->CurAnimation->currentFrame);
	}
	this->HandleKeyboard();
}

void PlayerUpwardState::HandleKeyboard() {
	if (keyCode[DIK_DOWNARROW]) {
		player->ChangeAnimation(new PlayerUpState());
	}
	else {
		player->y = player->y + CAR_BBOX_HEIGHT;
		player->ChangeAnimation(new PlayerStandingState());
		player->IsUp = false;
	}
}