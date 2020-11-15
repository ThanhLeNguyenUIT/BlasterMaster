#include "PlayerClimbingState.h"

PlayerClimbingState::PlayerClimbingState() {

	playerSmall->RenderOneFrame = false;
	playerSmall->vx = 0;
	if (playerSmall->ny > 0) {
		StateName = JASON_CLIMBING;
		playerSmall->vy = -JASON_MOVING_SPEED;
	}
	else {
		StateName = JASON_CLIMBING;
		playerSmall->vy = JASON_MOVING_SPEED;
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