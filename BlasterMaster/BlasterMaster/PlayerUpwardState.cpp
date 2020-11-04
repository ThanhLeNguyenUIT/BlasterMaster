#include "PlayerUpwardState.h"
#include "PlayerMovingState.h"
#include "PlayerJumpingState.h"
#include "PlayerStandingState.h"
#include "PlayerUpwardMovingState.h"

PlayerUpwardState::PlayerUpwardState() {
	if(!player->IsJumping)
		player->y = player->y - (SOPHIA_UP_BBOX_HEIGHT - SOPHIA_BBOX_HEIGHT) ;
	player->IsUp = true;
	player->renderOneFrame = false;

	player->vx = 0;

	if (player->nx > 0) {
			StateName = static_cast<STATENAME>(player->idFrame + 12);
	}
	else StateName = static_cast<STATENAME>(player->idFrame + 16);

	player->stateBoundingBox = SOPHIA_UP_BOUNDING_BOX;
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