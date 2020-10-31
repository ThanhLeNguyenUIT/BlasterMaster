#pragma once
#include "GameObject.h"
#include "PlayerState.h"
#include "Bullet.h"


#define SOPHIA_MOVING_SPEED             0.1f
#define SOPHIA_JUMP_SPEED_Y             0.8f
#define SOPHIA_GRAVITY                  0.001f
#define SOPHIA_JUMP_DEFLECT_SPEED     0.2f
#define SOPHIA_DIE_DEFLECT_SPEED	   0.5f

#define SOPHIA_ANIMATIONS_SET			1


class Sophia : public GameObject
{
	Bullet* bullet;
	vector<Bullet*> bullets;
	float start_x;			// initial position of Mario at scene
	float start_y;
public:
	int scene_id;
	static Sophia* _instance;
	int stateBoundingBox;
	PlayerState* state;
	Animation* CurAnimation;
	TYPE playerType;
	std::unordered_map<STATENAME, bool> allow;
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
	bool IsRenderBack = false;
	bool rev;
	int count = 0;
	int idFrame = 0;
	bool renderOneFrame = false;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	Sophia();
	~Sophia();
	void SetPlayerType(TYPE playerType) { this->playerType = playerType; }
	void ChangeAnimation(PlayerState* state, int stateChange = 0);
	static Sophia* GetInstance();
	void Fire();
	void DeleteBullet();
	void CheckState(int stateChange);
	void Reset(float x = 384, float y = 112);
	void OnKeyUp(int key);
	void OnKeyDown(int key);
};

