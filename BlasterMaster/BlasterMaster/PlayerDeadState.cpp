#include "PlayerDeadState.h"
#include "PlayerStandingState.h"

PlayerDeadState::PlayerDeadState() {
	if (Allow[SOPHIA]) {
		if (!player->IsDead)
			player->y = player->y - (SOPHIA_DEAD_BBOX_HEIGHT - SOPHIA_BBOX_HEIGHT);
		player->IsDead = true;
		player->RenderOneFrame = false;
		player->StateName = SOPHIA_DEAD;

		player->stateBoundingBox = SOPHIA_DEAD_BOUNDING_BOX;
	}
	else if (Allow[JASON]) {
		playerSmall->IsDead = true;
		playerSmall->RenderOneFrame = false;
		if (playerSmall->nx > 0)
			playerSmall->StateName = JASON_DEAD_RIGHT;
		else playerSmall->StateName = JASON_DEAD_LEFT;

		playerSmall->stateBoundingBox = JASON_BOUNDING_BOX;
	}
}

PlayerDeadState::~PlayerDeadState() {

}

void PlayerDeadState::Update() {

	this->HandleKeyboard();
}

void PlayerDeadState::HandleKeyboard() {
	if (Allow[SOPHIA]) {
		if (player->CurAnimation->isLastFrame) {
			if (player->IsDead) {
				player->IsRender = false;
				Allow[SOPHIA] = false;
				player->ChangeAnimation(new PlayerStandingState());
			}
		}
	}
	else if (Allow[JASON]) {
		if (playerSmall->CurAnimation->isLastFrame) {
			Allow[JASON] = false;
			playerSmall->IsRender = false;
		}
	}
}