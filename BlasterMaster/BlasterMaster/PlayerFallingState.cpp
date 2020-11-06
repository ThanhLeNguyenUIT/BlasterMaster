#include "PlayerFallingState.h"
#include "PlayerStandingState.h"
#include "PlayerJumpingState.h"
#include "PlayerJumpTurningState.h"

PlayerFallingState::PlayerFallingState() {
	if (Allow[SOPHIA]) {
		player->RenderOneFrame = true;
		if (player->nx > 0) {
			StateName = SOPHIA_FALLING_RIGHT;
		}
		else {
			StateName = SOPHIA_FALLING_LEFT;
		}
		player->stateBoundingBox = SOPHIA_BOUNDING_BOX;
	}
	else if (Allow[JASON]) {
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
	if (Allow[SOPHIA]) {
		if (!player->IsJumping) {
			player->ChangeAnimation(new PlayerStandingState(), NORMAL);
			return;
		}
	}
	else if (Allow[JASON]) {
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
		if (Allow[SOPHIA]) {
			if (player->nx > 0) {
				player->nx = 1;
				player->vx = SOPHIA_MOVING_SPEED;
				player->ChangeAnimation(new PlayerFallingState(), NORMAL);
				player->RenderOneFrame = false;
			}
			else {
				player->vx = -SOPHIA_MOVING_SPEED;
				player->ChangeAnimation(new PlayerJumpTurningState(), NORMAL);
				player->CurAnimation->currentFrame = -1;
				player->CurAnimation->isLastFrame = false;
			}
		}
		else if (Allow[JASON]) {
			playerSmall->nx = 1;
			playerSmall->vx = JASON_MOVING_SPEED;
			playerSmall->ChangeAnimation(new PlayerFallingState());
			player->RenderOneFrame = false;
		}
	}
	else if ((keyCode[DIK_LEFT]))
	{
		if (Allow[SOPHIA]) {
			if (player->nx < 0) {
				player->nx = -1;
				player->vx = -SOPHIA_MOVING_SPEED;
				player->ChangeAnimation(new PlayerFallingState(), NORMAL);
				player->RenderOneFrame = false;
			}
			else {
				player->vx = SOPHIA_MOVING_SPEED;
				player->ChangeAnimation(new PlayerJumpTurningState(), NORMAL);
				player->CurAnimation->currentFrame = -1;
				player->CurAnimation->isLastFrame = false;
			}
		}
		else if (Allow[JASON]) {
			playerSmall->nx = -1;
			playerSmall->vx = -JASON_MOVING_SPEED;
			playerSmall->ChangeAnimation(new PlayerFallingState());
		}
	}	
}
