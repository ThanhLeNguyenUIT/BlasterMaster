#pragma once
#include <Windows.h>
#define END_FIRST_SCENE 2032
#define HIGHEST_FIRST_SCENE 1048
#define	LOWEST_FIRST_SCENE 1302
#define START_FIRST_SCENE 1024

#define END_SECOND_SCENE 512
#define HIGHEST_SECOND_SCENE 0
#define	LOWEST_SECOND_SCENE 1312
#define START_SECOND_SCENE 0

#define END_3RD_SCENE 1040
#define HIGHEST_3RD_SCENE 0
#define	LOWEST_3RD_SCENE 680
#define START_3RD_SCENE 512

#define END_4TH_SCENE	512 
#define HIGHEST_4TH_SCENE 0
#define	LOWEST_4TH_SCENE 1024
#define START_4TH_SCENE 0

#define END_5TH_SCENE	1040
#define HIGHEST_5TH_SCENE 256
#define	LOWEST_5TH_SCENE 2080
#define START_5TH_SCENE 512

#define END_6TH_SCENE	1536
#define HIGHEST_6TH_SCENE 256
#define	LOWEST_6TH_SCENE 512
#define START_6TH_SCENE 1024

#define END_7TH_SCENE	2064
#define HIGHEST_7TH_SCENE 256
#define	LOWEST_7TH_SCENE 816
#define START_7TH_SCENE 1536

#define END_8TH_SCENE	1552
#define HIGHEST_8TH_SCENE 496
#define	LOWEST_8TH_SCENE 788
#define START_8TH_SCENE 1024

#define END_9TH_SCENE	1536
#define HIGHEST_9TH_SCENE 800
#define	LOWEST_9TH_SCENE 1056
#define START_9TH_SCENE 1008

class Camera {
	static Camera* __instance;
	float camPosX, camPosY;
	int width, height;
	
public:
	static Camera* GetInstance();
	bool isChangingMap = false;
	void SetCamPos(float x, float y) { camPosX = x; camPosY = y; }
	float GetCamPosX() { return camPosX; }
	float GetCamPosY() { return camPosY; }
	void Update();

	Camera();
	~Camera();
};