#pragma once 
#include "GameObject.h"
#define STAIR_BBOX_WIDTH 16
#define STAIR_BBOX_HEIGHT 16

class Stair : public GameObject
{
public:
	int boxWidth;
	int boxHeight;
	Stair(int boxWidth = 0, int boxHeight = 0);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Render();
};


