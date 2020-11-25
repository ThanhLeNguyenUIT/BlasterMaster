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
	int health = 8;
	float oldCx, oldCy;
	int scene_id = 1;
	static Sophia* _instance;
	int stateBoundingBox;
	PlayerState* state;
	Animation* CurAnimation;
	STATENAME StateName;
	TYPE playerType;
	std::unordered_map<TYPE, bool> allow;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	//bool IsJumping() { return this->isJumping; }
	bool IsJumping = false;
	bool IsOnGround;
	bool IsWalking;
	bool IsStop;
	bool IsLoad = true;
	bool IsFiring = false;
	bool IsDead = false;
	bool IsUp = false;
	bool IsTouchPortal;
	bool IsRender = true;
	bool IsTouchStair;
	bool IsUntouchable = false;
	bool IsOpen = false;
	bool IsMoving = false;
	//bool IsLoad = false;
	bool IsChangeScene = false;
	DWORD timeStartAttack = TIME_DEFAULT;
	DWORD timeDamaged = TIME_DEFAULT;
	int count = 0;
	int idFrame = 0;
	bool RenderOneFrame = false;
	bool RenderBack = false;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	Sophia();
	~Sophia();
	void SetPlayerType(TYPE playerType) { this->playerType = playerType; }
	void ChangeAnimation(PlayerState* state, int stateChange = 0);
	void ChangeScene();
	static Sophia* GetInstance();
	void CheckState(int stateChange);
	void Reset(float x = 67 * BIT, float y = 72 * BIT);
	void OnKeyUp(int key);
	void OnKeyDown(int key);
};

