#include "PlayerFallingState.h"
#include "PlayerFallingMovingState.h"
#include "PlayerStandingState.h"
#include "PlayerJumpingState.h"

PlayerFallingState::PlayerFallingState() {
	if (player->allow[SOPHIA]) {
		player->renderOneFrame = true;
		if (player->nx > 0) {
			StateName = SOPHIA_FALLING_RIGHT;
		}
		else {
			StateName = SOPHIA_FALLING_LEFT;
		}
		player->stateBoundingBox = SOPHIA_BOUNDING_BOX;
	}
	else if (player->allow[JASON]) {
		if (playerSmall->nx > 0) {
			StateName = JASON_FALLING_RIGHT;
		}
		else {
			StateName = JASON_FALLING_LEFT;
		}
		playerSmall->stateBoundingBox = JASON_BOUNDING_BOX;
	}
}

PlayerFallingState::~PlayerFallingState() {

}

void PlayerFallingState::Update() {
	if (player->allow[SOPHIA]) {
		if (!player->IsJumping) {
			player->ChangeAnimation(new PlayerStandingState(), NORMAL);
			return;
		}
	}
	else if (player->allow[JASON]) {
		if (!playerSmall->IsJumping) {
			playerSmall->ChangeAnimation(new PlayerStandingState());
			return;
		}
	}
	this->HandleKeyboard();
}

void PlayerFallingState::HandleKeyboard() {
	if ((keyCode[DIK_RIGHT]))
	{
		if (player->allow[SOPHIA]) {
			player->nx = 1;
			player->ChangeAnimation(new PlayerFallingMovingState(), NORMAL);
		}
		else if (player->allow[JASON]) {
			playerSmall->nx = 1;
			playerSmall->ChangeAnimation(new PlayerFallingMovingState());
		}
	}
	else if ((keyCode[DIK_LEFT]))
	{
		if (player->allow[SOPHIA]) {
			player->nx = -1;
			player->ChangeAnimation(new PlayerFallingMovingState(), NORMAL);
		}
		else if (player->allow[JASON]) {
			playerSmall->nx = -1;
			playerSmall->ChangeAnimation(new PlayerFallingMovingState());
		}
	}
	else {
		if(player->allow[SOPHIA])
			player->ChangeAnimation(new PlayerFallingState(), NORMAL);
		else if(player->allow[JASON])
			playerSmall->ChangeAnimation(new PlayerFallingState());
	}
		
}
