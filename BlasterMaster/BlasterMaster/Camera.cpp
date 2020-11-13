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
	float oldCx, oldCy = 0;
	if (Allow[SOPHIA]) {
		player->GetPosition(cx, cy);
	}
	else if (Allow[JASON])
		playerSmall->GetPosition(cx, cy);
	// when car up
	if (player->IsUp) {
		cy += 16;
	}
	// when car jump
	if (player->IsJumping) {
		cy = player->oldCy;
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
	SetCamPos(cx, cy);
}