#pragma once
#include "GameObject.h"
#include "PlayerState.h"
#include "Bullet.h"


#define JASON_MOVING_SPEED             0.1f
#define JASON_JUMP_SPEED_Y             0.8f
#define JASON_GRAVITY                  0.001f
#define JASON_JUMP_DEFLECT_SPEED     0.2f
#define JASON_DIE_DEFLECT_SPEED	   0.5f

#define JASON_ANIMATIONS_SET			2


class Jason : public GameObject
{
	Bullet* bullet;
	vector<Bullet*> bullets;
	float start_x;			// initial position of Jason at scene
	float start_y;
public:
	int scene_id;
	static Jason* _instance;
	int stateBoundingBox;
	PlayerState* state;
	Animation* CurAnimation;
	TYPE playerType;
	std::unordered_map<TYPE, bool> allow;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	//bool IsJumping() { return this->isJumping; }
	bool IsJumping;
	bool IsOnGround;
	bool IsWalking;
	bool IsStop;
	bool IsFiring;
	bool IsDead;
	bool IsUp;
	bool IsTouchPortal;
	bool IsUntouchable = false;
	bool IsOpen = false;
	bool IsRender = false;
	bool rev;
	int count = 0;
	int idFrame = 0;
	bool renderOneFrame = false;
	bool RenderBack = false;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	Jason();
	~Jason();
	void SetPlayerType(TYPE playerType) { this->playerType = playerType; }
	void ChangeAnimation(PlayerState* state, int stateChange = 0);
	static Jason* GetInstance();
	//void Fire();
	//void DeleteBullet();
	//void CheckState(int stateChange);
	void Reset(float x = 384, float y = 112);
	void OnKeyUp(int key);
	void OnKeyDown(int key);
};

