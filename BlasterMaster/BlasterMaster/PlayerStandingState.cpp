#include "PlayerStandingState.h"
#include "PlayerMovingState.h"
#include "PlayerUpwardState.h"
#include "PlayerTurningState.h"

PlayerStandingState::PlayerStandingState() {
	player->vx = 0;
	player->vy = 0;
	player->renderOneFrame = true;
	player->IsRenderBack = false;

	if (player->nx > 0)  {
		StateName = STANDING_RIGHT;
	}
	else{
		StateName = STANDING_LEFT;
	}
	player->stateBoundingBox = SOPHIA_BOUNDING_BOX;
}

PlayerStandingState::~PlayerStandingState() {

}

void PlayerStandingState::Update() {

	this->HandleKeyboard();
}

void PlayerStandingState::HandleKeyboard() {
	if (keyCode[DIK_LEFT] && keyCode[DIK_RIGHT]) {
		player->ChangeAnimation(new PlayerStandingState(), NORMAL);
	}
	else if (keyCode[DIK_LEFT]) {
		if (player->nx < 0)
			player->ChangeAnimation(new PlayerMovingState(), STAND_TO_MOVE);
		else
		{
			player->ChangeAnimation(new PlayerTurningState(), NORMAL);
			player->CurAnimation->currentFrame = -1;
			player->CurAnimation->isLastFrame = false;
		}

			
	}
	else if (keyCode[DIK_RIGHT]) {
		if (player->nx > 0)
			player->ChangeAnimation(new PlayerMovingState(), STAND_TO_MOVE);
		else
		{
			player->ChangeAnimation(new PlayerTurningState(), NORMAL);
			player->CurAnimation->currentFrame = -1;
			player->CurAnimation->isLastFrame = false;
		}
			
	}
	else if (keyCode[DIK_UPARROW]) {
		player->ChangeAnimation(new PlayerUpwardState());
	}
}