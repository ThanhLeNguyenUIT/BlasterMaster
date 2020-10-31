#pragma once
#include <d3dx9.h>
#include <d3d9.h>
#include <dinput.h>
#include <WinUser.h>
#include <unordered_map>
#include <vector>
#include <iostream> 
#include <string> 
#include <unordered_set> 
#include <map>
#include "debug.h"

using namespace std;

///// CAR /////
#define SOPHIA_MOVING_SPEED				0.01f
#define SOPHIA_JUMPING_SPEED_Y             0.4f
#define SOPHIA_GRAVITY						0.001f
#define SOPHIA_JUMPING_DEFLECT_SPEED		0.2f
#define SOPHIA_DIE_DEFLECT_SPEED			0.5f

#define SOPHIA_STATE_IDLE					0
#define SOPHIA_STATE_MOVING_RIGHT			100
#define SOPHIA_STATE_MOVING_LEFT			200
#define SOPHIA_STATE_JUMPING_RIGHT			300
#define SOPHIA_STATE_JUMPING_LEFT			400
#define SOPHIA_STATE_JUMPING				500
#define SOPHIA_STATE_FIRING				600

#define SOPHIA_STATE_DIE			4

#define SOPHIA_BOUNDING_BOX	111
#define SOPHIA_UP_BOUNDING_BOX 112

#define SOPHIA_BBOX_WIDTH		26
#define SOPHIA_BBOX_HEIGHT		18

#define SOPHIA_UP_BBOX_WIDTH 26
#define SOPHIA_UP_BBOX_HEIGHT 34
//CAR ANIMATIONS ID //

// STATE CHANGE
#define STAND_TO_MOVE		1
#define MOVE_TO_NORMAL		2
#define NORMAL				3
#define UPWARD_TO_NORMAL	4
#define TURN_TO_NORMAL		5

//// SCREEN /////
//#define SCREEN_WIDTH 320
//#define SCREEN_HEIGHT 240

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define TITLE_WIDTH 32
#define TITLE_HEIGHT 32

#define BIT 16
/// variable ///
extern std::unordered_map<int, bool> keyCode;	// manage info keycode have been pressed or not
#define GAME Game::GetInstance()
#define player Sophia::GetInstance()
extern std::unordered_map<int, bool> Allow;

extern enum STATENAME {
	STANDING_RIGHT,
	STANDING_LEFT,
	MOVING_RIGHT,
	MOVING_LEFT,
	JUMPING_RIGHT,
	JUMPING_LEFT,
	FALLING_RIGHT,
	FALLING_LEFT,
	JUMPING_MOVING_RIGHT,
	JUMPING_MOVING_LEFT,
	FALLING_MOVING_RIGHT,
	FALLING_MOVING_LEFT,
	UPWARD_RIGHT_0,
	UPWARD_RIGHT_1,
	UPWARD_RIGHT_2,
	UPWARD_RIGHT_3,
	UPWARD_LEFT_0,
	UPWARD_LEFT_1,
	UPWARD_LEFT_2,
	UPWARD_LEFT_3,
	UPWARD_MOVING_RIGHT,
	UPWARD_MOVING_LEFT,
	TURN_0,
	TURN_1,
	TURN_2,
	TURN_3,
	JUMPING_TURN_0,
	JUMPING_TURN_1,
	JUMPING_TURN_2,
	JUMPING_TURN_3,
	DEAD,
	OPEN
};

extern enum STATEOBJECT {
	BULLET_SMALL_MOVING_RIGHT,
	BULLET_SMALL_MOVING_LEFT,
	BULLET_SMALL_MOVING_UP,
	BULLET_SMALL_HIT,
	BULLET_BIG_MOVING_RIGHT,
	BULLET_BIG_MOVING_LEFT,
	BULLET_BIG_MOVING_UP,
	BULLET_BIG_HIT,
	BULLET_ELECTRIC,
	BRICK_NORMAL
};

extern enum TYPE {
	PLAYER,
	SOPHIA,
	JASON,
	BULLET_SMALL,
	BULLET_BIG,
	BRICK
};

extern enum  TAG
{
	/*PLAYER,
	ENEMY ,
	BOX ,
	ITEM ,
	EFFECT */
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