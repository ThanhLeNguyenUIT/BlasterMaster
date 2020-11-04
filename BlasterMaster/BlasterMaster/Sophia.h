#pragma once
#include "GameObject.h"
#include "PlayerState.h"
#include "Bullet.h"


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
	std::unordered_map<TYPE, bool> allow;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	//bool IsJumping() { return this->isJumping; }
	bool IsJumping = false;
	bool IsOnGround;
	bool IsWalking;
	bool IsStop;
	bool IsFiring;
	bool IsDead;
	bool IsUp = false;
	bool IsTouchPortal;
	bool IsUntouchable = false;
	bool IsOpen = false;
	bool rev;
	bool GunUp = false;
	bool IsMoving = true;
	int count = 0;
	int idFrame = 0;
	bool renderOneFrame = false;
	bool RenderBack = false;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	Sophia();
	~Sophia();
	void SetPlayerType(TYPE playerType) { this->playerType = playerType; }
	void ChangeAnimation(PlayerState* state, int stateChange = 0);
	static Sophia* GetInstance();
	void Fire();
	void DeleteBullet();
	void CheckState(int stateChange);
	void Reset(float x = 560, float y = 112);
	void OnKeyUp(int key);
	void OnKeyDown(int key);
};

