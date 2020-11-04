#include "PlayerStandingState.h"
#include "PlayerJumpingState.h"
#include "PlayerJumpingMovingState.h"
#include "PlayerFallingState.h"
#include "PlayerFallingMovingState.h"

PlayerFallingMovingState::PlayerFallingMovingState() {
	if (player->allow[SOPHIA]) {
		player->renderOneFrame = false;

		if (!player->IsJumping) {
			player->vy = -SOPHIA_JUMPING_SPEED_Y;
		}
		if (player->nx > 0) {
			StateName = SOPHIA_FALLING_MOVING_RIGHT;
		}
		else {
			StateName = SOPHIA_FALLING_MOVING_LEFT;
		}
		player->stateBoundingBox = SOPHIA_BOUNDING_BOX;
	}
	else if (player->allow[JASON]) {
		if (!playerSmall->IsJumping) {
			player->vy = -SOPHIA_JUMPING_SPEED_Y;
		}
		if (playerSmall->nx > 0) {
			StateName = JASON_JUMPING_RIGHT;
		}
		else {
			StateName = JASON_JUMPING_LEFT;
		}
		playerSmall->stateBoundingBox = JASON_BOUNDING_BOX;
	}
}

PlayerFallingMovingState::~PlayerFallingMovingState() {

}

void PlayerFallingMovingState::Update() {
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

void PlayerFallingMovingState::HandleKeyboard() {

}
