#include "Camera.h"
#include "Sophia.h"
#include "PlayerMovingState.h"
#include "PlayerStandingState.h"

Camera* Camera::__instance = NULL;

Camera* Camera::GetInstance()
{
	if (__instance == NULL) __instance = new Camera();
	return __instance;
}

Camera::Camera()
{
	camPosX = camPosY = 0;
	this->width = SCREEN_WIDTH;
	this->height = SCREEN_HEIGHT;
}

Camera::~Camera() {}

void Camera::Update()
{
	float cx, cy;
	float oldCx, oldCy;
	if (Allow[SOPHIA]) {
		player->GetPosition(cx, cy);
	}
	else if (Allow[JASON])
		playerSmall->GetPosition(cx, cy);
	if (player->IsUp) {
		cy += 16;
	}
	Game* game = Game::GetInstance();
	cx -= game->GetScreenWidth() / 2;
	cy -= game->GetScreenHeight() / 2;

	if (cx < 0) {
		cx = 0;
	}
	if (cy < 0) {
		cy = 0;
	}
	if (cx + width >= 2048) {
		cx = 2048 - width;
	}
	if (!player->IsTouchPortal) {
		SetCamPos(cx, cy);
	}
	/*if (cx + (512-player->x) >= 512) {
		cx = 521 - player->x;
	}*/
	// Update camera change scene for SOPHIA
	

	// Update camera change scene for JASON
	if (playerSmall->IsTouchPortal && Allow[JASON]) {
		playerSmall->ChangeAnimation(new PlayerMovingState());
		playerSmall->vy = 0;
		switch (playerSmall->scene_id) {
		case 0:
			// set end of scene 1 and start of scene 2
			if (playerSmall->x >= 560 && playerSmall->nx > 0) {
				playerSmall->ChangeAnimation(new PlayerStandingState());
				playerSmall->IsTouchPortal = false;
			}
			else if (playerSmall->x <= 432 && playerSmall->nx < 0) {
				playerSmall->ChangeAnimation(new PlayerStandingState());
				playerSmall->IsTouchPortal = false;
			}
			//set camera scene 1

			SetCamPos(cx, cy);
			break;
		case 1:
			if (playerSmall->x >= 1088 && playerSmall->nx > 0) {
				playerSmall->ChangeAnimation(new PlayerStandingState());
				playerSmall->IsTouchPortal = false;
			}
			else if (playerSmall->x <= 960 && playerSmall->nx < 0) {
				playerSmall->ChangeAnimation(new PlayerStandingState());
				playerSmall->IsTouchPortal = false;
			}
			break;
			SetCamPos(cx, cy);
		}
	}

	SetCamPos(cx, cy);
}