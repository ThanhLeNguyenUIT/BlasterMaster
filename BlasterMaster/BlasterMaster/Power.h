#pragma once
#include "Item.h"

class Power : public Item {
public:
	int power = 1;
	Animation* CurAnimation;
	Power();
	~Power();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();

	void ChangeAnimation(STATEOBJECT StateObject);
};