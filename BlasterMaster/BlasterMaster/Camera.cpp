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
	if (player->allow[SOPHIA])
		player->GetPosition(cx, cy);
	else if (player->allow[JASON])
		playerSmall->GetPosition(cx, cy);
	Game* game = Game::GetInstance();
	cx -= game->GetScreenWidth() / 2;
	cy -= game->GetScreenHeight() / 2;

	if (cx < 0) {
		cx = 0;
	}
	if (cy < 0) {
		cy = 0;
	}
	if (!player->IsTouchPortal) {
		SetCamPos(cx, cy);
	}
	/*if (cx + (512-player->x) >= 512) {
		cx = 521 - player->x;
	}*/
	// Update camera change scene
	if (player->IsTouchPortal) {
		player->ChangeAnimation(new PlayerMovingState());
		player->vy = 0;
		switch (player->scene_id) {
		case 0:
			// set end of scene 1 and start of scene 2
			if (player->x >= 560 && player->nx > 0) {
				player->ChangeAnimation(new PlayerStandingState());
				player->IsTouchPortal = false;
			}
			else if (player->x <= 432 && player->nx < 0) {
				player->ChangeAnimation(new PlayerStandingState());
				player->IsTouchPortal = false;
			}
			//set camera scene 1
			
			SetCamPos(cx, cy);
			break;
		case 1:
			if (player->x >= 1088 && player->nx > 0) {
				player->ChangeAnimation(new PlayerStandingState());
				player->IsTouchPortal = false;
			}
			else if (player->x <= 960 && player->nx < 0) {
				player->ChangeAnimation(new PlayerStandingState());
				player->IsTouchPortal = false;
			}
			break;
			SetCamPos(cx, cy);
		}
	}

	SetCamPos(cx, cy);
}