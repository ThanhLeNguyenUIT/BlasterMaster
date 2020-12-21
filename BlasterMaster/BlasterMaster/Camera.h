#pragma once
#include <Windows.h>
#define END_FIRST_SCENE 2032
#define HIGHEST_FIRST_SCENE 1032
#define	LOWEST_FIRST_SCENE 1302
#define START_FIRST_SCENE 1024

#define END_SECOND_SCENE 528
#define HIGHEST_SECOND_SCENE 16
#define	LOWEST_SECOND_SCENE 1318
#define START_SECOND_SCENE 0

#define END_3RD_SCENE 1040
#define HIGHEST_3RD_SCENE 16
#define	LOWEST_3RD_SCENE 688
#define START_3RD_SCENE 512

#define END_4TH_SCENE	512 
#define HIGHEST_4TH_SCENE 0
#define	LOWEST_4TH_SCENE 1024
#define START_4TH_SCENE 0

#define END_5TH_SCENE	1040
#define HIGHEST_5TH_SCENE 288
#define	LOWEST_5TH_SCENE 2080
#define START_5TH_SCENE 512

#define END_6TH_SCENE	1536
#define HIGHEST_6TH_SCENE 256
#define	LOWEST_6TH_SCENE 526
#define START_6TH_SCENE 1024

#define END_7TH_SCENE	2064
#define HIGHEST_7TH_SCENE 264
#define	LOWEST_7TH_SCENE 816
#define START_7TH_SCENE 1536

#define END_8TH_SCENE	1552
#define HIGHEST_8TH_SCENE 512
#define	LOWEST_8TH_SCENE 782
#define START_8TH_SCENE 1024

#define END_9TH_SCENE	1536
#define HIGHEST_9TH_SCENE 784
#define	LOWEST_9TH_SCENE 1054
#define START_9TH_SCENE 1008

#define TOP_OVERWORLD_1 736
#define BOTTOM_OVERWORLD_1 1292
#define LEFT_OVERWORLD_1 1280
#define RIGHT_OVERWORLD_1 1520

#define TOP_OVERWORLD_2 113 * BIT
#define BOTTOM_OVERWORLD_2  126 * BIT
#define LEFT_OVERWORLD_2 0
#define RIGHT_OVERWORLD_2 15 * BIT

#define TOP_OVERWORLD_3 1 * BIT
#define BOTTOM_OVERWORLD_3  13 * BIT
#define LEFT_OVERWORLD_3 0
#define RIGHT_OVERWORLD_3 31 * BIT

#define TOP_OVERWORLD_4 1 * BIT
#define BOTTOM_OVERWORLD_4  29 * BIT
#define LEFT_OVERWORLD_4 32 * BIT
#define RIGHT_OVERWORLD_4 63 * BIT

#define TOP_OVERWORLD_5 14 * BIT
#define BOTTOM_OVERWORLD_5  45 * BIT
#define LEFT_OVERWORLD_5 0
#define RIGHT_OVERWORLD_5 31 * BIT

#define TOP_BOSS_ZONE 65*BIT
#define BOTTOM_BOSS_ZONE 65*BIT +270
#define LEFT_BOSS_ZONE 110*BIT
#define RIGHT_BOSS_ZONE 2030

class Camera {
	static Camera* __instance;
	int width, height;
	
public:
	float camPosX, camPosY;
	static Camera* GetInstance();
	bool isChangingMap = false;
	bool isInTransition = false;
	void SetCamPos(float x, float y) { camPosX = x; camPosY = y; }
	float GetCamPosX() { return camPosX; }
	float GetCamPosY() { return camPosY; }
	void Update();
	RECT GetBound();
	Camera();
	~Camera();
};