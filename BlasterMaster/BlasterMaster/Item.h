#pragma once
#include "GameObject.h"

class Item : public GameObject {
public:
	bool IsTouch = false;
	Item();
	~Item();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) = 0;
	virtual void Render() = 0;
};