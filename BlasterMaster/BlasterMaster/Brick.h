#pragma once
#include "GameObject.h"

class Brick : public GameObject {
public:
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	Brick();
};