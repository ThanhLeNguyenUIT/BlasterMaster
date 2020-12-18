#pragma once
#include "Enemy.h"
#include "EnemyBullet.h"

class Canon : public Enemy
{
public:
	DWORD timenow = TIME_DEFAULT;
	Animation* CurAnimation;
	EnemyBullet* bullet1 = NULL;
	EnemyBullet* bullet2 = NULL;
	EnemyBullet* bullet3 = NULL;
	EnemyBullet* bullet4 = NULL;
	DWORD timeStartAttack = TIME_DEFAULT;
	DWORD timeDamaged = TIME_DEFAULT;
	void ChangeAnimation(STATEOBJECT StateObject);
	STATEOBJECT GetStateObject() { return this->StateObject; }
	void SetType(TYPE type) { this->type = type; }
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	bool isRender = true;
	Canon() {
		type = CANON;
		width = CANON_BBOX_WIDTH;
		height = DOME_BBOX_HEIGHT;
		ChangeAnimation(CANON_MOVING);
	}
	virtual void Render();
	void Fire();
};

