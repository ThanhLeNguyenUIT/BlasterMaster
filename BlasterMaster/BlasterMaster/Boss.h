#pragma once
#include "Enemy.h"
#include "BossArm.h"
#include "BossHand.h"


class CBoss : public Enemy
{
	bool isHit = false;
	int old_nx;
	int old_ny;
public:
	static CBoss* _instance;
	bool IsRender;
	bool isWakingUp = true;
	bool isMoving = false;
	//CBossBullet* bullet;8888
	vector<CBossArm*> listBossArm;
	vector<CBossHand*> listBossHand;
	//vector<CBossBullet*> listBossBullet;
	DWORD timeStartAttack = TIME_DEFAULT;
	Animation* CurAnimation;
	CBoss(float x = 118 * BIT, float y = 66 * BIT);
	bool CheckIsHit() { return isHit; }
	void ChangeAnimation(STATEOBJECT StateObject);
	STATEOBJECT GetStateObject() { return this->StateObject; }
	void SetType(TYPE type) {  }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void Reset();
	void Sleep();
	void Move();
	void WakeUp();
	static CBoss* GetInstance();
	void Fire();
};