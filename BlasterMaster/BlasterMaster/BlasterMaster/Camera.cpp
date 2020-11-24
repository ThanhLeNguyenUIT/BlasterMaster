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
	int currentSceneID;
	if (Allow[SOPHIA]) {
		player->GetPosition(cx, cy);
		currentSceneID = player->scene_id;
	}
	else if (Allow[JASON]) {
		playerSmall->GetPosition(cx, cy);
		currentSceneID = playerSmall->scene_id;
	}
	else if (Allow[BIG_JASON]) {
		playerBig->GetPosition(cx, cy);
		currentSceneID = playerBig->scene_id;
	}
	if (player->IsDead) {
		cx = player->x;
		cy = player->y;
		currentSceneID = player->scene_id;
	}
	if (playerSmall->IsDead) {
		cx = playerSmall->x;
		cy = playerSmall->y;
		currentSceneID = playerSmall->scene_id;
	}
	Game* game = Game::GetInstance();
	cx -= game->GetScreenWidth() / 2;
	cy -= game->GetScreenHeight() / 2;
	switch (currentSceneID) {
	case 1:
		if (cx < START_FIRST_SCENE) {
			cx = START_FIRST_SCENE;
		}
		else if (cx + width >= END_FIRST_SCENE) {
			cx = END_FIRST_SCENE - width;
		}

		if (cy < HIGHEST_FIRST_SCENE) {
			cy = HIGHEST_FIRST_SCENE;
		}
		else if (cy + height > LOWEST_FIRST_SCENE)
		{
			cy = LOWEST_FIRST_SCENE - height;
		}
		break;
	case 2:
		if (cx < START_SECOND_SCENE) {
			cx = START_SECOND_SCENE;
		}
		else if (cx + width >= END_SECOND_SCENE) {
			cx = END_SECOND_SCENE - width;
		}

		if (cy < HIGHEST_SECOND_SCENE) {
			cy = HIGHEST_SECOND_SCENE;
		}
		else if (cy + height > LOWEST_SECOND_SCENE)
		{
			cy = LOWEST_SECOND_SCENE - height;
		}
		break;
	case 3:
		if (cx < START_3RD_SCENE) {
			cx = START_3RD_SCENE;
		}
		else if (cx + width >= END_3RD_SCENE) {
			cx = END_3RD_SCENE - width;
		}

		if (cy < HIGHEST_3RD_SCENE) {
			cy = HIGHEST_3RD_SCENE;
		}
		else if (cy + height > LOWEST_3RD_SCENE)
		{
			cy = LOWEST_3RD_SCENE - height;
		}
		break;
	case 4:
		if (cx < START_4TH_SCENE) {
			cx = START_4TH_SCENE;
		}
		else if (cx + width >= END_4TH_SCENE) {
			cx = END_4TH_SCENE - width;
		}

		if (cy < HIGHEST_4TH_SCENE) {
			cy = HIGHEST_4TH_SCENE;
		}
		else if (cy + height > LOWEST_4TH_SCENE)
		{
			cy = LOWEST_4TH_SCENE - height;
		}
		break;
	case 5:
		if (cx < START_5TH_SCENE) {
			cx = START_5TH_SCENE;
		}
		else if (cx + width >= END_5TH_SCENE) {
			cx = END_5TH_SCENE - width;
		}

		if (cy < HIGHEST_5TH_SCENE) {
			cy = HIGHEST_5TH_SCENE;
		}
		else if (cy + height > LOWEST_5TH_SCENE)
		{
			cy = LOWEST_5TH_SCENE - height;
		}
		break;
	case 6:
		if (cx < START_6TH_SCENE) {
			cx = START_6TH_SCENE;
		}
		else if (cx + width >= END_6TH_SCENE) {
			cx = END_6TH_SCENE - width;
		}

		if (cy < HIGHEST_6TH_SCENE) {
			cy = HIGHEST_6TH_SCENE;
		}
		else if (cy + height > LOWEST_6TH_SCENE)
		{
			cy = LOWEST_6TH_SCENE - height;
		}
		break;
	case 7:
		if (cx < START_7TH_SCENE) {
			cx = START_7TH_SCENE;
		}
		else if (cx + width >= END_7TH_SCENE) {
			cx = END_7TH_SCENE - width;
		}

		if (cy < HIGHEST_7TH_SCENE) {
			cy = HIGHEST_7TH_SCENE;
		}
		else if (cy + height > LOWEST_7TH_SCENE)
		{
			cy = LOWEST_7TH_SCENE - height;
		}
		break;
	case 8:
		if (cx < START_8TH_SCENE) {
			cx = START_8TH_SCENE;
		}
		else if (cx + width >= END_8TH_SCENE) {
			cx = END_8TH_SCENE - width;
		}

		if (cy < HIGHEST_8TH_SCENE) {
			cy = HIGHEST_8TH_SCENE;
		}
		else if (cy + height > LOWEST_8TH_SCENE)
		{
			cy = LOWEST_8TH_SCENE - height;
		}
		break;
	case 9:
		if (cx < START_9TH_SCENE) {
			cx = START_9TH_SCENE;
		}
		else if (cx + width >= END_9TH_SCENE) {
			cx = END_9TH_SCENE - width;
		}

		if (cy < HIGHEST_9TH_SCENE) {
			cy = HIGHEST_9TH_SCENE;
		}
		else if (cy + height > LOWEST_9TH_SCENE)
		{
			cy = LOWEST_9TH_SCENE - height;
		}
		break;
		/*case 10:
			if (cx < START_FIRST_SCENE) {
				cx = START_FIRST_SCENE;
			}
			else if (cx + width >= END_FIRST_SCENE) {
				cx = END_FIRST_SCENE - width;
			}

			if (cy < HIGHEST_FIRST_SCENE) {
				cy = HIGHEST_FIRST_SCENE;
			}
			else if (cy + height > LOWEST_FIRST_SCENE)
			{
				cy = LOWEST_FIRST_SCENE - height;
			}
			break;*/

		if (!player->IsTouchPortal)
		{
			SetCamPos(cx, cy);
		}
	}
	if (player->IsUp) {
		cy += 6;
	}

	SetCamPos(cx, cy);
}