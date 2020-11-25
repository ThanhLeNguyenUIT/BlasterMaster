#include "PlayerStandingState.h"
#include "PlayerMovingState.h"
#include "PlayerUpwardState.h"
#include "PlayerUpperState.h"
#include "PlayerUpwardMovingState.h"
#include "GlobalConfig.h"

PlayerMovingState::PlayerMovingState(DWORD timeFinish) {
	/////////// SOPHIA ////////////
	if (Allow[SOPHIA]) {
		player->RenderOneFrame = false;
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
	else if (Allow[JASON]) {
		playerSmall->RenderOneFrame = false;
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

void PlayerMovingState::walking(DWORD PosTarX)
{
	if (player->IsTouchPortal)  {
		if (player->x < PosTarX) {
			if (player->x >= PosTarX - 2) {
				timeFinish = 0;
				player->ChangeAnimation(new PlayerStandingState());
				//player->SetSpeed(0, 0);
				player->IsWalkingComplete = true;
				return;
			}
		}
		else
		{
			if (player->x <= PosTarX + 2) {
				timeFinish = 0;
				player->ChangeAnimation(new PlayerStandingState());
				//player->SetSpeed(0, 0);
				player->IsWalkingComplete = true;
				return;
			}
		}
		player->ChangeAnimation(new PlayerMovingState(PosTarX));
	}
}

void PlayerMovingState::Update() {
	/*if ((!player->IsWalkingComplete) && (timeFinish !=0)) {
		walking(timeFinish);
	}
	else */ this->HandleKeyboard();
}

void PlayerMovingState::HandleKeyboard() {
	if (keyCode[DIK_RIGHT] && keyCode[DIK_LEFT]) {
		/////////// SOPHIA ////////////
		if (Allow[SOPHIA])
			player->ChangeAnimation(new PlayerStandingState(), MOVE_TO_NORMAL);
		/////////// JASON /////////////////
		else if (Allow[JASON])
			playerSmall->ChangeAnimation(new PlayerStandingState());
	}
	else if (keyCode[DIK_UP]) {
		/////////// SOPHIA ////////////
		if (Allow[SOPHIA]) {
			if(!player->IsUp)
				player->y = player->y - (SOPHIA_UP_BBOX_HEIGHT - SOPHIA_BBOX_HEIGHT);
			player->IsUp = true;
			player->ChangeAnimation(new PlayerUpperState(), MOVE_TO_NORMAL);
		}
	}
	else if (keyCode[DIK_RIGHT]) {
		/////////// SOPHIA ////////////
		if (Allow[SOPHIA]) {
			player->nx = 1;
			player->ChangeAnimation(new PlayerMovingState(), NORMAL);
		}
		/////////// JASON /////////////////
		else if (Allow[JASON]) {
			playerSmall->nx = 1;
			playerSmall->ChangeAnimation(new PlayerMovingState());
		}
	}
	else if (keyCode[DIK_LEFT]) {
		/////////// SOPHIA ////////////
		if (Allow[SOPHIA]) {
			player->nx = -1;
			player->ChangeAnimation(new PlayerMovingState(), NORMAL);
		}
		/////////// JASON /////////////////
		if (Allow[JASON]) {
			playerSmall->nx = -1;
			playerSmall->ChangeAnimation(new PlayerMovingState());
		}
	}
	else {
		if (Allow[SOPHIA])
			player->ChangeAnimation(new PlayerStandingState(), MOVE_TO_NORMAL);
		if (Allow[JASON])
			playerSmall->ChangeAnimation(new PlayerStandingState());
	}
}