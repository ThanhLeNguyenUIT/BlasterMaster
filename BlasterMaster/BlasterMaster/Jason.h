
#pragma once
#include "GameObject.h"
#include "PlayerState.h"
#include "Bullet.h"


class Jason : public GameObject
{
public:
	Bullet* bullet;
	float oldCx, oldCy;
	int health = 8;
	int scene_id;
	int scene_gate;
	static Jason* _instance;
	int stateBoundingBox;
	PlayerState* state;
	STATENAME StateName;
	Animation* CurAnimation;
	TYPE playerType;
	std::unordered_map<TYPE, bool> allow;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	DWORD timeStartAttack = TIME_DEFAULT;
	DWORD timeDamaged = TIME_DEFAULT;
	bool IsJumping;
	bool IsOnGround;
	bool IsMoving;
	bool IsStop;
	bool IsCrawling = false;
	bool IsFiring = false;
	bool IsDead;
	bool IsUp;
	bool IsTouchPortal;
	bool IsTouchStair;
	bool IsTouchGate;
	bool IsUntouchable = false;
	bool IsOpen = false;
	bool IsRender;
	bool IsGravity = true;
	//bool IsLoad = true;
	bool RenderOneFrame = false;
	bool rev;
	int count = 0;
	int idFrame = 0;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	Jason();
	~Jason();
	void SetPlayerType(TYPE playerType) { this->playerType = playerType; }
	void ChangeAnimation(PlayerState* state, int stateChange = 0);
	void ChangeScene();
	static Jason* GetInstance();
	void Reset(float x = 384, float y = 112);
	void OnKeyUp(int key);
	void OnKeyDown(int key);
};

