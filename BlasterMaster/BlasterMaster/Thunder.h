#pragma once
#include "Item.h"

class Thunder : public Item {
public:
	int power = 1;
	Animation* CurAnimation;
	Thunder();
	~Thunder();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();

	void ChangeAnimation(STATEOBJECT StateObject);
};