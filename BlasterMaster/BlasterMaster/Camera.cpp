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

RECT Camera::GetBound() {
	RECT rect;

	rect.left = camPosX;
	rect.top = camPosY;
	rect.right = camPosX + width;
	rect.bottom = camPosY + height;

	return rect;
}

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
	case 53:
		if (cx < LEFT_BOSS_ZONE) {
			cx = LEFT_BOSS_ZONE;
		}
		else if (cx + width >= RIGHT_BOSS_ZONE) {
			cx = RIGHT_BOSS_ZONE - width;
		}
		if (cy < TOP_BOSS_ZONE) {
			cy = TOP_BOSS_ZONE;
		}
		else if (cy + height > BOTTOM_BOSS_ZONE)
		{
			cy = BOTTOM_BOSS_ZONE - height;
		}
		break;
	case 40:
		if (cx < LEFT_OVERWORLD_3) {
			cx = LEFT_OVERWORLD_3;
		}
		else if (cx + width >= RIGHT_OVERWORLD_3) {
			cx = RIGHT_OVERWORLD_3 - width + 30;
		}
		if (cy < TOP_OVERWORLD_3) {
			cy = TOP_OVERWORLD_3;
		}
		else if (cy + height > BOTTOM_OVERWORLD_3)
		{
			cy = BOTTOM_OVERWORLD_3 - height + 78;
		}
		break;
	case 41:
		if (cx < LEFT_OVERWORLD_4) {
			cx = LEFT_OVERWORLD_4;
		}
		else if (cx + width >= RIGHT_OVERWORLD_4) {
			cx = RIGHT_OVERWORLD_4 - width + 30;
		}
		if (cy < TOP_OVERWORLD_4) {
			cy = TOP_OVERWORLD_4;
		}
		else if (cy + height > BOTTOM_OVERWORLD_4)
		{
			cy = BOTTOM_OVERWORLD_4 - height + 78;
		}
		break;
	case 50:
		if (cx < LEFT_OVERWORLD_5) {
			cx = LEFT_OVERWORLD_5;
		}
		else if (cx + width >= RIGHT_OVERWORLD_5) {
			cx = RIGHT_OVERWORLD_5 - width + 30;
		}
		if (cy < TOP_OVERWORLD_5) {
			cy = TOP_OVERWORLD_5;
		}
		else if (cy + height > BOTTOM_OVERWORLD_5)
		{
			cy = BOTTOM_OVERWORLD_5 - height + 78;
		}
		break;
	case 51:
		if (cx < 32 * BIT) {
			cx = 32 * BIT;
		}
		else if (cx + width >= 47 * BIT) {
			cx = 47 * BIT - width + 30;
		}
		if (cy < 33 * BIT) {
			cy = 33 * BIT;
		}
		else if (cy + height > 46 * BIT)
		{
			cy = 46 * BIT - height + 62;
		}
		break;
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
			cy = HIGHEST_FIRST_SCENE;
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
	case 10:
		if (cx < LEFT_OVERWORLD_1) {
			cx = LEFT_OVERWORLD_1;
		}
		else if (cx + width >= RIGHT_OVERWORLD_1) {
			cx = RIGHT_OVERWORLD_1 - width + 30;
		}
		if (cy < TOP_OVERWORLD_1) {
			cy = TOP_OVERWORLD_1;
		}
		else if (cy + height > BOTTOM_OVERWORLD_1)
		{
			cy = BOTTOM_OVERWORLD_1 - height;
		}
		break;
	case 11:
		if (cx < LEFT_OVERWORLD_2) {
			cx = LEFT_OVERWORLD_2;
		}
		else if (cx + width >= RIGHT_OVERWORLD_2) {
			cx = RIGHT_OVERWORLD_2 - width + 30;
		}
		if (cy < TOP_OVERWORLD_2) {
			cy = TOP_OVERWORLD_2;
		}
		else if (cy + height > BOTTOM_OVERWORLD_2)
		{
			cy = BOTTOM_OVERWORLD_2 - height + 62;
		}
		break;
	case 12:
		if (cx < LEFT_OVERWORLD_2 + 256) {
			cx = LEFT_OVERWORLD_2 + 256;
		}
		else if (cx + width >= RIGHT_OVERWORLD_2 + 256) {
			cx = RIGHT_OVERWORLD_2 - width + 30 + 256;
		}
		if (cy < TOP_OVERWORLD_2) {
			cy = TOP_OVERWORLD_2;
		}
		else if (cy + height > BOTTOM_OVERWORLD_2)
		{
			cy = BOTTOM_OVERWORLD_2 - height + 62;
		}
		break;
	case 13:
		if (cx < LEFT_OVERWORLD_2 + 256 * 2) {
			cx = LEFT_OVERWORLD_2 + 256 * 2;
		}
		else if (cx + width >= RIGHT_OVERWORLD_2) {
			cx = RIGHT_OVERWORLD_2 - width + 30 + 256 * 2;
		}
		if (cy < TOP_OVERWORLD_2) {
			cy = TOP_OVERWORLD_2;
		}
		else if (cy + height > BOTTOM_OVERWORLD_2)
		{
			cy = BOTTOM_OVERWORLD_2 - height + 62;
		}
		break;
	case 14:
		if (cx < LEFT_OVERWORLD_2 + 256 * 3) {
			cx = LEFT_OVERWORLD_2 + 256 * 3;
		}
		else if (cx + width >= RIGHT_OVERWORLD_2) {
			cx = RIGHT_OVERWORLD_2 - width + 30 + 256 * 3;
		}
		if (cy < TOP_OVERWORLD_2) {
			cy = TOP_OVERWORLD_2;
		}
		else if (cy + height > BOTTOM_OVERWORLD_2)
		{
			cy = BOTTOM_OVERWORLD_2 - height + 62;
		}
		break;
	case 15:
		if (cx < LEFT_OVERWORLD_2 + 256 * 4) {
			cx = LEFT_OVERWORLD_2 + 256 * 4;
		}
		else if (cx + width >= RIGHT_OVERWORLD_2) {
			cx = RIGHT_OVERWORLD_2 - width + 30 + 256 * 4;
		}
		if (cy < TOP_OVERWORLD_2) {
			cy = TOP_OVERWORLD_2;
		}
		else if (cy + height > BOTTOM_OVERWORLD_2)
		{
			cy = BOTTOM_OVERWORLD_2 - height + 62;
		}
		break;
	case 16:
		if (cx < LEFT_OVERWORLD_2 + 256 * 5) {
			cx = LEFT_OVERWORLD_2 + 256 * 5;
		}
		else if (cx + width >= RIGHT_OVERWORLD_2) {
			cx = RIGHT_OVERWORLD_2 - width + 30 + 256 * 5;
		}
		if (cy < TOP_OVERWORLD_2) {
			cy = TOP_OVERWORLD_2;
		}
		else if (cy + height > BOTTOM_OVERWORLD_2)
		{
			cy = BOTTOM_OVERWORLD_2 - height + 62;
		}
		break;
	case 17:
		if (cx < LEFT_OVERWORLD_2 + 256 * 5) {
			cx = LEFT_OVERWORLD_2 + 256 * 5;
		}
		else if (cx + width >= RIGHT_OVERWORLD_2) {
			cx = RIGHT_OVERWORLD_2 - width + 30 + 256 * 5;
		}
		if (cy < TOP_OVERWORLD_2 - 256) {
			cy = TOP_OVERWORLD_2 - 256;
		}
		else if (cy + height > BOTTOM_OVERWORLD_2 - 256)
		{
			cy = BOTTOM_OVERWORLD_2 - height + 62 - 256;
		}
		break;
	case 18:
		if (cx < LEFT_OVERWORLD_2 + 256 * 4) {
			cx = LEFT_OVERWORLD_2 + 256 * 4;
		}
		else if (cx + width >= RIGHT_OVERWORLD_2) {
			cx = RIGHT_OVERWORLD_2 - width + 30 + 256 * 4;
		}
		if (cy < TOP_OVERWORLD_2 - 256) {
			cy = TOP_OVERWORLD_2 - 256;
		}
		else if (cy + height > BOTTOM_OVERWORLD_2 - 256)
		{
			cy = BOTTOM_OVERWORLD_2 - height + 62 - 256;
		}
		break;
	case 19:
		if (cx < LEFT_OVERWORLD_2 + 256 * 3) {
			cx = LEFT_OVERWORLD_2 + 256 * 3;
		}
		else if (cx + width >= RIGHT_OVERWORLD_2) {
			cx = RIGHT_OVERWORLD_2 - width + 30 + 256 * 3;
		}
		if (cy < TOP_OVERWORLD_2 - 256) {
			cy = TOP_OVERWORLD_2 - 256;
		}
		else if (cy + height > BOTTOM_OVERWORLD_2 - 256)
		{
			cy = BOTTOM_OVERWORLD_2 - height + 62 - 256;
		}
		break;
	case 20:
		if (cx < LEFT_OVERWORLD_2 + 256 * 2) {
			cx = LEFT_OVERWORLD_2 + 256 * 2;
		}
		else if (cx + width >= RIGHT_OVERWORLD_2 + 256 * 2) {
			cx = RIGHT_OVERWORLD_2 - width + 30 + 256 * 2;
		}
		if (cy < TOP_OVERWORLD_2 - 256) {
			cy = TOP_OVERWORLD_2 - 256;
		}
		else if (cy + height > BOTTOM_OVERWORLD_2 - 256)
		{
			cy = BOTTOM_OVERWORLD_2 - height + 62 - 256;
		}
		break;
	case 21:
		if (cx < LEFT_OVERWORLD_2 + 256) {
			cx = LEFT_OVERWORLD_2 + 256;
		}
		else if (cx + width >= RIGHT_OVERWORLD_2 + 256) {
			cx = RIGHT_OVERWORLD_2 - width + 30 + 256;
		}
		if (cy < TOP_OVERWORLD_2 - 256) {
			cy = TOP_OVERWORLD_2 - 256;
		}
		else if (cy + height > BOTTOM_OVERWORLD_2 - 256)
		{
			cy = BOTTOM_OVERWORLD_2 - height + 62 - 256;
		}
		break;
	case 22:
		if (cx < LEFT_OVERWORLD_2) {
			cx = LEFT_OVERWORLD_2;
		}
		else if (cx + width >= RIGHT_OVERWORLD_2) {
			cx = RIGHT_OVERWORLD_2 - width + 30;
		}
		if (cy < TOP_OVERWORLD_2 - 256) {
			cy = TOP_OVERWORLD_2 - 256;
		}
		else if (cy + height > BOTTOM_OVERWORLD_2 - 256)
		{
			cy = BOTTOM_OVERWORLD_2 - height + 62 - 256;
		}
		break;
	case 23:
		if (cx < LEFT_OVERWORLD_2) {
			cx = LEFT_OVERWORLD_2;
		}
		else if (cx + width >= RIGHT_OVERWORLD_2) {
			cx = RIGHT_OVERWORLD_2 - width + 30;
		}
		if (cy < TOP_OVERWORLD_2 - 256 * 2) {
			cy = TOP_OVERWORLD_2 - 256 * 2;
		}
		else if (cy + height > BOTTOM_OVERWORLD_2 - 256 * 2)
		{
			cy = BOTTOM_OVERWORLD_2 - height + 62 - 256 * 2;
		}
		break;
	case 24:
		if (cx < LEFT_OVERWORLD_2 + 256) {
			cx = LEFT_OVERWORLD_2 + 256;
		}
		else if (cx + width >= RIGHT_OVERWORLD_2 + 256) {
			cx = RIGHT_OVERWORLD_2 - width + 30 + 256;
		}
		if (cy < TOP_OVERWORLD_2 - 256 * 2) {
			cy = TOP_OVERWORLD_2 - 256 * 2;
		}
		else if (cy + height > BOTTOM_OVERWORLD_2 - 256 * 2)
		{
			cy = BOTTOM_OVERWORLD_2 - height + 62 - 256 * 2;
		}
		break;
	case 25:
		if (cx < LEFT_OVERWORLD_2 + 256 * 2) {
			cx = LEFT_OVERWORLD_2 + 256 * 2;
		}
		else if (cx + width >= RIGHT_OVERWORLD_2 + 256 * 2) {
			cx = RIGHT_OVERWORLD_2 - width + 30 + 256 * 2;
		}
		if (cy < TOP_OVERWORLD_2 - 256 * 2) {
			cy = TOP_OVERWORLD_2 - 256 * 2;
		}
		else if (cy + height > BOTTOM_OVERWORLD_2 - 256 * 2)
		{
			cy = BOTTOM_OVERWORLD_2 - height + 62 - 256 * 2;
		}
		break;
	case 26:
		if (cx < LEFT_OVERWORLD_2 + 256 * 3) {
			cx = LEFT_OVERWORLD_2 + 256 * 3;
		}
		else if (cx + width >= RIGHT_OVERWORLD_2) {
			cx = RIGHT_OVERWORLD_2 - width + 30 + 256 * 3;
		}
		if (cy < TOP_OVERWORLD_2 - 256 * 2) {
			cy = TOP_OVERWORLD_2 - 256 * 2;
		}
		else if (cy + height > BOTTOM_OVERWORLD_2 - 256 * 2)
		{
			cy = BOTTOM_OVERWORLD_2 - height + 62 - 256 * 2;
		}
		break;
	case 27:
		if (cx < LEFT_OVERWORLD_2 + 256 * 4) {
			cx = LEFT_OVERWORLD_2 + 256 * 4;
		}
		else if (cx + width >= RIGHT_OVERWORLD_2) {
			cx = RIGHT_OVERWORLD_2 - width + 30 + 256 * 4;
		}
		if (cy < TOP_OVERWORLD_2 - 256 * 2) {
			cy = TOP_OVERWORLD_2 - 256 * 2;
		}
		else if (cy + height > BOTTOM_OVERWORLD_2 - 256 * 2)
		{
			cy = BOTTOM_OVERWORLD_2 - height + 62 - 256 * 2;
		}
		break;
	case 28:
		if (cx < LEFT_OVERWORLD_2 + 256 * 5) {
			cx = LEFT_OVERWORLD_2 + 256 * 5;
		}
		else if (cx + width >= RIGHT_OVERWORLD_2) {
			cx = RIGHT_OVERWORLD_2 - width + 30 + 256 * 5;
		}
		if (cy < TOP_OVERWORLD_2 - 256 * 2) {
			cy = TOP_OVERWORLD_2 - 256 * 2;
		}
		else if (cy + height > BOTTOM_OVERWORLD_2 - 256 * 2)
		{
			cy = BOTTOM_OVERWORLD_2 - height + 62 - 256 * 2;
		}
		break;
	case 29:
		if (cx < LEFT_OVERWORLD_2 + 256 * 4) {
			cx = LEFT_OVERWORLD_2 + 256 * 4;
		}
		else if (cx + width >= RIGHT_OVERWORLD_2) {
			cx = RIGHT_OVERWORLD_2 - width + 30 + 256 * 4;
		}
		if (cy < TOP_OVERWORLD_2 - 256 * 3) {
			cy = TOP_OVERWORLD_2 - 256 * 3;
		}
		else if (cy + height > BOTTOM_OVERWORLD_2 - 256 * 3)
		{
			cy = BOTTOM_OVERWORLD_2 - height + 62 - 256 * 3;
		}
		break;
	case 30:
		if (cx < LEFT_OVERWORLD_2 + 256 * 3) {
			cx = LEFT_OVERWORLD_2 + 256 * 3;
		}
		else if (cx + width >= RIGHT_OVERWORLD_2) {
			cx = RIGHT_OVERWORLD_2 - width + 30 + 256 * 3;
		}
		if (cy < TOP_OVERWORLD_2 - 256 * 3) {
			cy = TOP_OVERWORLD_2 - 256 * 3;
		}
		else if (cy + height > BOTTOM_OVERWORLD_2 - 256 * 3)
		{
			cy = BOTTOM_OVERWORLD_2 - height + 62 - 256 * 3;
		}
		break;
	case 31:
		if (cx < LEFT_OVERWORLD_2 + 256 * 2) {
			cx = LEFT_OVERWORLD_2 + 256 * 2;
		}
		else if (cx + width >= RIGHT_OVERWORLD_2 + 256 * 2) {
			cx = RIGHT_OVERWORLD_2 - width + 30 + 256 * 2;
		}
		if (cy < TOP_OVERWORLD_2 - 256 * 3) {
			cy = TOP_OVERWORLD_2 - 256 * 3;
		}
		else if (cy + height > BOTTOM_OVERWORLD_2 - 256 * 3)
		{
			cy = BOTTOM_OVERWORLD_2 - height + 62 - 256 * 3;
		}
		break;
	case 32:
		if (cx < LEFT_OVERWORLD_2 + 256) {
			cx = LEFT_OVERWORLD_2 + 256;
		}
		else if (cx + width >= RIGHT_OVERWORLD_2 + 256) {
			cx = RIGHT_OVERWORLD_2 - width + 30 + 256;
		}
		if (cy < TOP_OVERWORLD_2 - 256 * 3) {
			cy = TOP_OVERWORLD_2 - 256 * 3;
		}
		else if (cy + height > BOTTOM_OVERWORLD_2 - 256 * 3)
		{
			cy = BOTTOM_OVERWORLD_2 - height + 62 - 256 * 3;
		}
		break;
	case 33:
		if (cx < LEFT_OVERWORLD_2) {
			cx = LEFT_OVERWORLD_2;
		}
		else if (cx + width >= RIGHT_OVERWORLD_2) {
			cx = RIGHT_OVERWORLD_2 - width + 30;
		}
		if (cy < TOP_OVERWORLD_2 - 256 * 3) {
			cy = TOP_OVERWORLD_2 - 256 * 3;
		}
		else if (cy + height > BOTTOM_OVERWORLD_2 - 256 * 3)
		{
			cy = BOTTOM_OVERWORLD_2 - height + 62 - 256 * 3;
		}
		break;
	case 34:
		if (cx < LEFT_OVERWORLD_2) {
			cx = LEFT_OVERWORLD_2;
		}
		else if (cx + width >= RIGHT_OVERWORLD_2) {
			cx = RIGHT_OVERWORLD_2 - width + 30;
		}
		if (cy < TOP_OVERWORLD_2 - 256 * 4) {
			cy = TOP_OVERWORLD_2 - 256 * 4;
		}
		else if (cy + height > BOTTOM_OVERWORLD_2 - 256 * 4)
		{
			cy = BOTTOM_OVERWORLD_2 - height + 62 - 256 * 4;
		}
		break;
	case 35:
		if (cx < LEFT_OVERWORLD_2 + 256) {
			cx = LEFT_OVERWORLD_2 + 256;
		}
		else if (cx + width >= RIGHT_OVERWORLD_2 + 256) {
			cx = RIGHT_OVERWORLD_2 - width + 30 + 256;
		}
		if (cy < TOP_OVERWORLD_2 - 256 * 4) {
			cy = TOP_OVERWORLD_2 - 256 * 4;
		}
		else if (cy + height > BOTTOM_OVERWORLD_2 - 256 * 4)
		{
			cy = BOTTOM_OVERWORLD_2 - height + 62 - 256 * 4;
		}
		break;
	case 36:
		if (cx < LEFT_OVERWORLD_2 + 256 * 2) {
			cx = LEFT_OVERWORLD_2 + 256 * 2;
		}
		else if (cx + width >= RIGHT_OVERWORLD_2 + 256 * 2) {
			cx = RIGHT_OVERWORLD_2 - width + 30 + 256 * 2;
		}
		if (cy < TOP_OVERWORLD_2 - 256 * 4) {
			cy = TOP_OVERWORLD_2 - 256 * 4;
		}
		else if (cy + height > BOTTOM_OVERWORLD_2 - 256 * 4)
		{
			cy = BOTTOM_OVERWORLD_2 - height + 62 - 256 * 4;
		}
		break;
	case 37:
		if (cx < LEFT_OVERWORLD_2 + 256 * 3) {
			cx = LEFT_OVERWORLD_2 + 256 * 3;
		}
		else if (cx + width >= RIGHT_OVERWORLD_2) {
			cx = RIGHT_OVERWORLD_2 - width + 30 + 256 * 3;
		}
		if (cy < TOP_OVERWORLD_2 - 256 * 4) {
			cy = TOP_OVERWORLD_2 - 256 * 4;
		}
		else if (cy + height > BOTTOM_OVERWORLD_2 - 256 * 4)
		{
			cy = BOTTOM_OVERWORLD_2 - height + 62 - 256 * 4;
		}
		break;
	case 38:
		if (cx < LEFT_OVERWORLD_2 + 256 * 4) {
			cx = LEFT_OVERWORLD_2 + 256 * 4;
		}
		else if (cx + width >= RIGHT_OVERWORLD_2) {
			cx = RIGHT_OVERWORLD_2 - width + 30 + 256 * 4;
		}
		if (cy < TOP_OVERWORLD_2 - 256 * 4) {
			cy = TOP_OVERWORLD_2 - 256 * 4;
		}
		else if (cy + height > BOTTOM_OVERWORLD_2 - 256 * 4)
		{
			cy = BOTTOM_OVERWORLD_2 - height + 62 - 256 * 4;
		}
		break;
	case 39:
		if (cx < LEFT_OVERWORLD_2 + 256 * 3) {
			cx = LEFT_OVERWORLD_2 + 256 * 3;
		}
		else if (cx + width >= RIGHT_OVERWORLD_2) {
			cx = RIGHT_OVERWORLD_2 - width + 30 + 256 * 3;
		}
		if (cy < TOP_OVERWORLD_2 - 256 * 5) {
			cy = TOP_OVERWORLD_2 - 256 * 5;
		}
		else if (cy + height > BOTTOM_OVERWORLD_2 - 256 * 5)
		{
			cy = BOTTOM_OVERWORLD_2 - height + 62 - 256 * 5;
		}
		break;

		if (!player->IsTouchPortal)
		{
			SetCamPos(cx, cy);
		}
	}

	// add to fix camera 
	if (player->IsUp && player->scene_id != 1 && player->scene_id != 3 && player->scene_id != 6 && player->scene_id != 9) {
		if (!(((player->scene_id == 2) && (cy == HIGHEST_SECOND_SCENE)) || ((player->scene_id == 7) && (cy == HIGHEST_7TH_SCENE))|| ((player->scene_id == 8) && (cy == HIGHEST_8TH_SCENE)))) {
			cy += 16;
		}
	}

	if ((player->IsUp) && ((player->scene_id == 5) && (cy == HIGHEST_5TH_SCENE + 16))) {
		cy -= 16;
	}

	if ((player->IsUp) && ((player->scene_id == 4) && (cy == HIGHEST_4TH_SCENE + 16))) {
		cy -= 16;
	}

	if ((player->IsUp) && ((player->scene_id == 5) && (cy + 270 >= LOWEST_5TH_SCENE))) {
		cy -= 16;
	}


	if ((player->IsUp) && ((player->scene_id == 2) && (cy + 270 >= LOWEST_SECOND_SCENE))) {
		cy -= 16;
	}

	if ((player->IsUp) && ((player->scene_id == 4) && (cy + 270 >= LOWEST_4TH_SCENE))) {
		cy -= 16;
	}

	if ((player->IsUp) && ((player->scene_id == 7) && (cy + 270 >= LOWEST_7TH_SCENE))) {
		cy -= 16;
	}
	if ((player->IsUp) && ((player->scene_id == 8) && (cy + 270 >= LOWEST_8TH_SCENE))) {
		cy -= 16;
	}

	SetCamPos(cx, cy);
}