#include "PlayerClimbingState.h"

PlayerClimbingState::PlayerClimbingState() {

	playerSmall->RenderOneFrame = false;
	playerSmall->vx = 0;
	if (playerSmall->ny > 0) {
		playerSmall->StateName = JASON_CLIMBING;
		playerSmall->vy = -JASON_CLIMBING_SPEED;
	}
	else {
		playerSmall->StateName = JASON_CLIMBING;
		playerSmall->vy = JASON_CLIMBING_SPEED;
	}
	playerSmall->stateBoundingBox = JASON_BOUNDING_BOX;
}

PlayerClimbingState::~PlayerClimbingState() {

}

void PlayerClimbingState::Update() {
	this->HandleKeyboard();
}

void PlayerClimbingState::HandleKeyboard() {

}