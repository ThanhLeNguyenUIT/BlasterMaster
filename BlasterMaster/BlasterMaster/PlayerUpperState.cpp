#include "PlayerUpperState.h"
#include "PlayerMovingState.h"
#include "PlayerUpwardMovingState.h"

PlayerUpperState::PlayerUpperState() {
	if (!player->IsJumping && !player->IsUp)
		player->y = player->y - (SOPHIA_UP_BBOX_HEIGHT - SOPHIA_BBOX_HEIGHT);
	player->RenderOneFrame = false;
	player->IsUp = true;
	if (player->nx > 0) {
		player->StateName = static_cast<STATENAME>(player->idFrame + 8);
		if (player->StateName > 11) {
			player->StateName = static_cast<STATENAME>( player->StateName - 4);
		}
		player->CurAnimation->currentFrame = player->count;
	}
	else {
		player->StateName = static_cast<STATENAME>(player->idFrame + 12);
		if (player->StateName > 15) {
			player->StateName = static_cast<STATENAME>(player->StateName - 4);
		}
		player->CurAnimation->currentFrame = player->count;
	}
	player->stateBoundingBox = SOPHIA_UP_BOUNDING_BOX;
}

PlayerUpperState::~PlayerUpperState() {

}

void PlayerUpperState::Update() {
	
	this->HandleKeyboard();
}

void PlayerUpperState::HandleKeyboard() {
	if (player->count >= 3) {
		player->CurAnimation->currentFrame = -1;
		if (keyCode[DIK_RIGHT]) {
			player->nx = 1;
			player->ChangeAnimation(new PlayerUpwardMovingState());
		}
		else if (keyCode[DIK_LEFT]) {
			player->nx = -1;
			player->ChangeAnimation(new PlayerUpwardMovingState());
		}
		else if (keyCode[DIK_UP]) {
			player->ChangeAnimation(new PlayerUpperState());
			player->CurAnimation->currentFrame = 3;
		}
	}
}