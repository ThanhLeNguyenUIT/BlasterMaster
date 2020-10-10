#pragma once
#include <d3dx9.h>
#include <d3d9.h>
#include <dinput.h>
#include <WinUser.h>
#include <unordered_map>
//#include "Camera.h"
#include <vector>
#include <iostream> 
#include <string> 
#include <unordered_set> 
#include <map>
#include "debug.h"

using namespace std;

///// CAR /////
#define CAR_MOVING_SPEED				0.01f
#define CAR_JUMPING_SPEED_Y             0.4f
#define CAR_GRAVITY						0.001f
#define CAR_JUMPING_DEFLECT_SPEED		0.2f
#define CAR_DIE_DEFLECT_SPEED			0.5f

#define CAR_STATE_IDLE					0
#define CAR_STATE_MOVING_RIGHT			100
#define CAR_STATE_MOVING_LEFT			200
#define CAR_STATE_JUMPING_RIGHT			300
#define CAR_STATE_JUMPING_LEFT			400
#define CAR_STATE_JUMPING				500
#define CAR_STATE_FIRING				600
#define CAR_STATE_NOT_FIRING			700

#define CAR_ANI_IDLE_RIGHT		0
#define CAR_ANI_IDLE_LEFT		1
#define CAR_ANI_MOVING_RIGHT	2
#define CAR_ANI_MOVING_LEFT		3

#define CAR_STATE_DIE			4

#define CAR_BOUNDING_BOX	111
#define CAR_UP_BOUNDING_BOX 112

#define CAR_BBOX_WIDTH		26
#define CAR_BBOX_HEIGHT		18

#define CAR_UP_BBOX_WIDTH 26
#define CAR_UP_BBOX_HEIGHT 34

//// SCREEN /////
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define TITLE_WIDTH 32
#define TITLE_HEIGHT 32

#define ID_TEX_CAR		0
#define ID_TEX_ENEMY	10
#define ID_TEX_MISC		20
#define ID_TEX_BULLET	30

/// variable ///

extern std::unordered_map<int, bool> keyCode;	// manage info keycode have been pressed or not
#define GAME CGame::GetInstance()
#define player CCar::GetInstance()
extern std::unordered_map<int, bool> Allow;

extern enum STATENAME {
	STANDING,
	STANDING_RIGHT,
	STANDING_LEFT,
	MOVING,
	MOVING_RIGHT,
	MOVING_LEFT,
	TURN,
	TURN_RIGHT,
	TURN_LEFT,
	JUMPING,
	JUMPING_RIGHT,
	JUMPING_LEFT,
	JUMPING_MOVING_RIGHT,
	JUMPING_MOVING_LEFT,
	FALLING,
	FALLING_RIGHT,
	FALLING_LEFT,
	FALLING_MOVING_RIGHT,
	FALLING_MOVING_LEFT,
	UP,
	UP_RIGHT,
	UP_LEFT,
	UP_MOVING_RIGHT,
	UP_MOVING_LEFT,
	UPWARD,
	UPWARD_RIGHT,
	UPWARD_LEFT,
	UPWARD_MOVING_RIGHT,
	UPWARD_MOVING_LEFT,
	UPWARD_JUMPING_RIGHT,
	UPWARD_JUMPING_LEFT,
	DEAD
};

extern enum  TAG
{
	PLAYER,
	ENEMY,
	BOX,
	ITEM,
	EFFECT
};

//extern std::unordered_map<std::string, TYPE>   TYPEString;
//
//#define ADDITEM(x)  TYPEString.insert(std::pair<std::string,TYPE>(#x,x));
//
extern std::unordered_map<std::string, STATENAME>   STATEString;

#define ADDSTATE(x)  STATEString.insert(std::pair<std::string,STATENAME>(#x,x));

class CGlobalConfig
{
public:
	CGlobalConfig() {};
	~CGlobalConfig() {};
};