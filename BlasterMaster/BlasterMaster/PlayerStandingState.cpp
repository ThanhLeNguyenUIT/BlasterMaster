#include "PlayerStandingState.h"
#include "PlayerMovingState.h"
#include "PlayerUpwardState.h"
#include "PlayerTurningState.h"

PlayerStandingState::PlayerStandingState() {
	if (player->allow[SOPHIA]) {
		player->vx = 0;
		player->IsMoving = false;
		player->renderOneFrame = true;
		player->RenderBack = false;

		if (player->nx > 0) {
			StateName = SOPHIA_STANDING_RIGHT;
		}
		else {
			StateName = SOPHIA_STANDING_LEFT;
		}
		player->stateBoundingBox = SOPHIA_BOUNDING_BOX;
	}
	else if (player->allow[JASON]) {
		playerSmall->vx = 0;
		playerSmall->vy = 0;

		if (playerSmall->nx > 0) {
			StateName = JASON_STANDING_RIGHT;
		}
		else {
			StateName = JASON_STANDING_LEFT;
		}
		playerSmall->stateBoundingBox = JASON_BOUNDING_BOX;
	}
}

PlayerStandingState::~PlayerStandingState() {

}

void PlayerStandingState::Update() {

	this->HandleKeyboard();
}

void PlayerStandingState::HandleKeyboard() {
	if (keyCode[DIK_LEFT] && keyCode[DIK_RIGHT]) {
		if (player->allow[SOPHIA])
			player->ChangeAnimation(new PlayerStandingState(), NORMAL);
		else if (player->allow[JASON])
			playerSmall->ChangeAnimation(new PlayerStandingState());
	}
	else if (keyCode[DIK_LEFT]) {
		if (player->allow[SOPHIA]) {
			if (player->nx < 0)
				player->ChangeAnimation(new PlayerMovingState(), STAND_TO_MOVE);
			else
			{
				player->ChangeAnimation(new PlayerTurningState(), NORMAL);
				player->CurAnimation->currentFrame = -1;
				player->CurAnimation->isLastFrame = false;
			}
		}
		else if (player->allow[JASON]) {
			playerSmall->ChangeAnimation(new PlayerMovingState());
		}

	}
	else if (keyCode[DIK_RIGHT]) {
		if (player->allow[SOPHIA]) {
			if (player->nx > 0)
				player->ChangeAnimation(new PlayerMovingState(), STAND_TO_MOVE);
			else
			{
				player->ChangeAnimation(new PlayerTurningState(), NORMAL);
				player->CurAnimation->currentFrame = -1;
				player->CurAnimation->isLastFrame = false;
			}
		}
		else if (player->allow[JASON]) {
			playerSmall->ChangeAnimation(new PlayerMovingState());
		}

	}
	else if (keyCode[DIK_UPARROW]) {
		if (player->allow[SOPHIA])
			player->ChangeAnimation(new PlayerUpwardState());
	}
}