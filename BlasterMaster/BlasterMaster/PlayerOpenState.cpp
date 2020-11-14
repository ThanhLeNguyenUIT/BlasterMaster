#include "PlayerOpenState.h"
#include "PlayerStandingState.h"
#include "Sophia.h"

PlayerOpenState::PlayerOpenState() {
	if (Allow[SOPHIA]) {
		player->vx = 0;
		if (player->nx > 0)
			StateName = SOPHIA_OPEN_RIGHT;
		else StateName = SOPHIA_OPEN_LEFT;
		player->stateBoundingBox = SOPHIA_OPEN_BOUNDING_BOX;
		player->y = player->y - (SOPHIA_OPEN_BBOX_HEIGHT - SOPHIA_BBOX_HEIGHT);
	}
}

PlayerOpenState::~PlayerOpenState() {

}

void PlayerOpenState::Update() {
	this->HandleKeyboard();
}

void PlayerOpenState::HandleKeyboard() {

}
