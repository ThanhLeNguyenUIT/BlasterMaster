#include "PlayerStandingState.h"
#include "PlayerMovingState.h"
#include "PlayerUpwardState.h"
#include "PlayerUpperState.h"
#include "PlayerUpwardMovingState.h"

PlayerMovingState::PlayerMovingState(DWORD timeFinish) {

	/////////// SOPHIA ////////////
	if (player->allow[SOPHIA]) {
		player->renderOneFrame = false;
		player->IsMoving = true;
		if (player->nx > 0) {

			StateName = SOPHIA_MOVING_RIGHT;
			player->vx = SOPHIA_MOVING_SPEED;
		}
		else {

			StateName = SOPHIA_MOVING_LEFT;
			player->vx = -SOPHIA_MOVING_SPEED;
		}

		player->stateBoundingBox = SOPHIA_BOUNDING_BOX;
	}
	/////////// JASON /////////////////
	else if (player->allow[JASON]) {
		if (playerSmall->nx > 0) {
			StateName = JASON_MOVING_RIGHT;
			playerSmall->vx = JASON_MOVING_SPEED;
		}
		else {
			StateName = JASON_MOVING_LEFT;
			playerSmall->vx = -JASON_MOVING_SPEED;
		}

		playerSmall->stateBoundingBox = JASON_BOUNDING_BOX;
	}
}

void PlayerMovingState::Update() {
	
	this->HandleKeyboard();
}

void PlayerMovingState::HandleKeyboard() {
	if (keyCode[DIK_RIGHT] && keyCode[DIK_LEFT]) {
		if (player->allow[SOPHIA])
			player->ChangeAnimation(new PlayerStandingState(), MOVE_TO_NORMAL);
		else if (player->allow[JASON])
			playerSmall->ChangeAnimation(new PlayerStandingState());
	}
	else if (keyCode[DIK_UP]) {
		if (player->allow[SOPHIA]) {
			if(!player->IsUp)
				player->y = player->y - (SOPHIA_UP_BBOX_HEIGHT - SOPHIA_BBOX_HEIGHT);
			player->IsUp = true;
			player->ChangeAnimation(new PlayerUpperState(), MOVE_TO_NORMAL);
		}
	}
	else if (keyCode[DIK_RIGHT]) {
		if (player->allow[SOPHIA]) {
			player->nx = 1;
			player->ChangeAnimation(new PlayerMovingState(), NORMAL);
		}
		else if (player->allow[JASON]) {
			playerSmall->nx = 1;
			playerSmall->ChangeAnimation(new PlayerMovingState());
		}
	}
	else if (keyCode[DIK_LEFT]) {
		if (player->allow[SOPHIA]) {
			player->nx = -1;
			player->ChangeAnimation(new PlayerMovingState(), NORMAL);
		}
		if (player->allow[JASON]) {
			playerSmall->nx = -1;
			playerSmall->ChangeAnimation(new PlayerMovingState());
		}
	}
	else {
		if (player->allow[SOPHIA])
			player->ChangeAnimation(new PlayerStandingState(), MOVE_TO_NORMAL);
		if (player->allow[JASON])
			playerSmall->ChangeAnimation(new PlayerStandingState());
	}
}