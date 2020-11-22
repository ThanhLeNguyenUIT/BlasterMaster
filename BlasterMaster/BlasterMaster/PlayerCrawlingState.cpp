#include "PlayerCrawlingState.h"

PlayerCrawlingState::PlayerCrawlingState() {

	playerSmall->vx = 0;
	if (!playerSmall->IsCrawling)
		playerSmall->y += (JASON_BBOX_HEIGHT - JASON_CRAWLING_BBOX_HEIGHT);
	if (playerSmall->nx > 0) {
		playerSmall->StateName = JASON_CRAWLING_RIGHT;
	}
	else playerSmall->StateName = JASON_CRAWLING_LEFT;

	playerSmall->stateBoundingBox = JASON_CRAWLING_BOUNDING_BOX;
}

PlayerCrawlingState::~PlayerCrawlingState() {

}

void PlayerCrawlingState::Update() {
	this->HandleKeyboard();
}

void PlayerCrawlingState::HandleKeyboard() {
	if (keyCode[DIK_RIGHT]) {
		playerSmall->nx = 1;
		playerSmall->ChangeAnimation(new PlayerCrawlingState());
		playerSmall->vx = JASON_MOVING_SPEED;
		playerSmall->RenderOneFrame = false;
	}
	else if (keyCode[DIK_LEFT]) {
		playerSmall->nx = -1;
		playerSmall->ChangeAnimation(new PlayerCrawlingState());
		playerSmall->vx = -JASON_MOVING_SPEED;
		playerSmall->RenderOneFrame = false;
	}
	else {
		playerSmall->ChangeAnimation(new PlayerCrawlingState());
		playerSmall->RenderOneFrame = true;
	}
}