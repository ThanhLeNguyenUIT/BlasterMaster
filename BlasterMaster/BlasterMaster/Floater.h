#pragma once
#include "Enemy.h"
#include "EnemyBullet.h"

class CFloater : public Enemy
{
public:
	EnemyBullet* bullet;
	DWORD timeStartAttack = TIME_DEFAULT;
	DWORD timeDamaged = TIME_DEFAULT;
	Animation* CurAnimation;
	CFloater();
	void ChangeAnimation(STATEOBJECT StateObject);
	void SetType(TYPE type) { this->type = type; }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void Reset();
	void Fire();
};