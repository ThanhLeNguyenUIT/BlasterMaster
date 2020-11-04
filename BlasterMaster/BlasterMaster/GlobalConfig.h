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

///// JASON /////
#define JASON_MOVING_SPEED             0.08f
#define JASON_JUMP_SPEED_Y             0.4f
#define JASON_GRAVITY                  0.001f
#define JASON_JUMP_DEFLECT_SPEED     0.2f
#define JASON_DIE_DEFLECT_SPEED	   0.5f

#define JASON_BOUNDING_BOX	114

#define JASON_BBOX_WIDTH	10
#define JASON_BBOX_HEIGHT	17
///// CAR /////
#define SOPHIA_MOVING_SPEED				0.1f
#define SOPHIA_JUMPING_SPEED_Y             0.4f
#define SOPHIA_GRAVITY						0.001f
#define SOPHIA_JUMPING_DEFLECT_SPEED		0.2f
#define SOPHIA_DIE_DEFLECT_SPEED			0.5f


#define SOPHIA_BOUNDING_BOX			111
#define SOPHIA_UP_BOUNDING_BOX		112
#define SOPHIA_OPEN_BOUNDING_BOX	113

#define SOPHIA_BBOX_WIDTH		26
#define SOPHIA_BBOX_HEIGHT		18

#define SOPHIA_UP_BBOX_WIDTH 26
#define SOPHIA_UP_BBOX_HEIGHT 34

#define SOPHIA_OPEN_BBOX_WIDTH	26
#define SOPHIA_OPEN_BBOX_HEIGHT	26
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
#define playerSmall Jason::GetInstance()


extern enum STATENAME {
	///// SOPHIA ///////
	SOPHIA_STANDING_RIGHT,
	SOPHIA_STANDING_LEFT,
	SOPHIA_MOVING_RIGHT,
	SOPHIA_MOVING_LEFT,
	SOPHIA_JUMPING_RIGHT,
	SOPHIA_JUMPING_LEFT,
	SOPHIA_FALLING_RIGHT,
	SOPHIA_FALLING_LEFT,
	SOPHIA_UPWARD_RIGHT_0,
	SOPHIA_UPWARD_RIGHT_1,
	SOPHIA_UPWARD_RIGHT_2,
	SOPHIA_UPWARD_RIGHT_3,
	SOPHIA_UPWARD_LEFT_0,
	SOPHIA_UPWARD_LEFT_1,
	SOPHIA_UPWARD_LEFT_2,
	SOPHIA_UPWARD_LEFT_3,
	SOPHIA_UPWARD_MOVING_RIGHT,
	SOPHIA_UPWARD_MOVING_LEFT,
	SOPHIA_TURN_0,
	SOPHIA_TURN_1,
	SOPHIA_TURN_2,
	SOPHIA_TURN_3,
	SOPHIA_JUMPING_TURN_0,
	SOPHIA_JUMPING_TURN_1,
	SOPHIA_JUMPING_TURN_2,
	SOPHIA_JUMPING_TURN_3,
	SOPHIA_DEAD,
	SOPHIA_OPEN,
	///// JASON ////////
	JASON_STANDING_RIGHT,
	JASON_STANDING_LEFT,
	JASON_MOVING_RIGHT,
	JASON_MOVING_LEFT,
	JASON_CLIMBING,
	JASON_CRAWLING_RIGHT,
	JASON_CRAWLING_LEFT,
	JASON_JUMPING_RIGHT,
	JASON_JUMPING_LEFT,
	JASON_FALLING_RIGHT,
	JASON_FALLING_LEFT
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
extern std::unordered_map<TYPE, bool> Allow;
#define ADDSTATE(x)  STATEString.insert(std::pair<std::string,STATENAME>(#x,x));

class CGlobalConfig
{
public:
	CGlobalConfig() {};
	~CGlobalConfig() {};
};