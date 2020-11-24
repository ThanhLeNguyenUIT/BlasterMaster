#include "PlayerUpperState.h"
#include "PlayerMovingState.h"
#include "PlayerUpwardMovingState.h"
#include "PlayerUpwardState.h"

PlayerUpperState::PlayerUpperState() {
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
	if (player->count >= 2) {
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
			player->ChangeAnimation(new PlayerUpwardMovingState());
			player->CurAnimation->currentFrame = 2;
			player->RenderOneFrame = true;
			player->vx = 0;
		}
	}
}