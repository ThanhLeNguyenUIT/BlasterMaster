#pragma once
#include "Item.h"

class Hover : public Item {
public:
	int power = 1;
	Animation* CurAnimation;
	Hover();
	~Hover();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();

	void ChangeAnimation(STATEOBJECT StateObject);
};