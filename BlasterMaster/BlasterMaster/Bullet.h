#pragma once
#include "GameObject.h"
#include "Enemy.h"
class Bullet : public GameObject {
public:
	int damage = 0;
	Bullet();
	~Bullet();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coStaticObjects, vector<Enemy*>* coEnemy = NULL) = 0;
	virtual void Render() = 0;
};