#include "PlayerJumpingMovingState.h"
#include "PlayerMovingState.h"
#include "PlayerFallingState.h"
#include "PlayerFallingMovingState.h"

PlayerJumpingMovingState::PlayerJumpingMovingState() {

	////// SOPHIA ///////////
	if (player->allow[SOPHIA]) {
		player->renderOneFrame = false;
		if (player->nx > 0) {
			player->vx = SOPHIA_MOVING_SPEED;
			StateName = SOPHIA_JUMPING_MOVING_RIGHT;
		}
		else {
			player->vx = -SOPHIA_MOVING_SPEED;
			StateName = SOPHIA_JUMPING_MOVING_LEFT;
		}
		player->stateBoundingBox = SOPHIA_BOUNDING_BOX;
	}
	
	////////////  JASON  /////////
	else if (player->allow[JASON]) {
		if (!playerSmall->IsJumping) {
			playerSmall->vy = -JASON_JUMP_SPEED_Y;
		}
		if (playerSmall->nx > 0) {
			playerSmall->vx = JASON_MOVING_SPEED;
			StateName = JASON_JUMPING_RIGHT;
		}
		else {
			playerSmall->vx = -JASON_MOVING_SPEED;
			StateName = JASON_JUMPING_LEFT;
		}
		playerSmall->stateBoundingBox = JASON_BOUNDING_BOX;
	}
}

PlayerJumpingMovingState::~PlayerJumpingMovingState() {

}

void PlayerJumpingMovingState::Update() {
	if (player->allow[SOPHIA]) {
		if (player->vy > 0) {
			player->ChangeAnimation(new PlayerFallingState(), NORMAL);
			return;
		}
	}
	else if (player->allow[JASON]) {
		if (playerSmall->vy > 0) {
			playerSmall->ChangeAnimation(new PlayerFallingState());
			return;
		}
	}
	this->HandleKeyboard();
}

void PlayerJumpingMovingState::HandleKeyboard() {
	
}