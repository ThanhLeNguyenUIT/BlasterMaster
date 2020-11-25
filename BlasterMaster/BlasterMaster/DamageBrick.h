#pragma once
#pragma once
#include "GameObject.h"

#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16

class DamageBrick : public GameObject {
public:
	int boxWidth;
	int boxHeight;
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	DamageBrick(int boxWidth = 0, int boxHeight = 0);
};