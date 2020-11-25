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
	float oldCx, oldCy;
	int scene_id = 1;
	int old_scene_id = 0;
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
	bool IsFiring = false;
	bool IsDead;
	bool IsUp = false;
	bool IsTouchPortal;
	bool IsRender = true;
	bool IsTouchGate;
	bool IsUntouchable = false;
	bool IsOpen = false;
	bool IsMoving = false;
	bool IsLoad = false;
	bool IsWalkingComplete = true;
	DWORD timeStartAttack = TIME_DEFAULT;
	int count = 0;
	int idFrame = 0;
	bool RenderOneFrame = false;
	bool RenderBack = false;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	bool right = false;
	Sophia();
	~Sophia();
	void SetPlayerType(TYPE playerType) { this->playerType = playerType; }
	void ChangeAnimation(PlayerState* state, int stateChange = 0);
	void ChangeScene(DWORD dt);
	static Sophia* GetInstance();
	void CheckState(int stateChange);
	void Reset(float x = 67 * BIT, float y = 72 * BIT);
	void OnKeyUp(int key);
	void OnKeyDown(int key);
};

