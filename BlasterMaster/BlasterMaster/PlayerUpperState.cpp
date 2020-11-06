#include "PlayerUpperState.h"
#include "PlayerMovingState.h"
#include "PlayerUpwardMovingState.h"

PlayerUpperState::PlayerUpperState() {
	player->RenderOneFrame = false;
	if (player->nx > 0) {
		StateName = static_cast<STATENAME>(player->idFrame + 8);
		if (StateName > 11) {
			StateName = static_cast<STATENAME>( StateName - 4);
		}
		player->CurAnimation->currentFrame = player->count;
	}
	else {
		StateName = static_cast<STATENAME>(player->idFrame + 12);
		if (StateName > 15) {
			StateName = static_cast<STATENAME>(StateName - 4);
		}
		player->CurAnimation->currentFrame = player->count;
	}
	player->stateBoundingBox = SOPHIA_UP_BOUNDING_BOX;
}

PlayerUpperState::~PlayerUpperState() {

}

void PlayerUpperState::Update() {
	if (player->count >= 2) {
		player->CurAnimation->currentFrame = -1;
		player->ChangeAnimation(new PlayerUpwardMovingState());
	}
	//this->HandleKeyboard();
}

void PlayerUpperState::HandleKeyboard() {

}