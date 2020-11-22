#include "PlayerUpwardState.h"
#include "PlayerMovingState.h"
#include "PlayerJumpingState.h"
#include "PlayerStandingState.h"
#include "PlayerUpwardMovingState.h"

PlayerUpwardState::PlayerUpwardState() {
	if(!player->IsJumping)
		player->y = player->y - (SOPHIA_UP_BBOX_HEIGHT - SOPHIA_BBOX_HEIGHT) ;
	player->IsUp = true;
	player->RenderOneFrame = false;

	//player->vx = 0;

	if (player->nx > 0) {
		player->StateName = static_cast<STATENAME>(player->idFrame + 8);
	}
	else player->StateName = static_cast<STATENAME>(player->idFrame + 12);

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
	else if (keyCode[DIK_RIGHT]) {
		player->nx = 1;
		player->ChangeAnimation(new PlayerUpwardMovingState());
	}
	else if (keyCode[DIK_LEFT]) {
		player->nx = -1;
		player->ChangeAnimation(new PlayerUpwardMovingState());
	}
}