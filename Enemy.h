#pragma once
#include "GameObject.h"

class Enemy : public GameObject
{
public:
	int health = 3;
	STATEOBJECT StateObject;
	Enemy();
	~Enemy();
	virtual void Render() = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) = 0;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
};