#pragma once
#pragma once
#include "GameObject.h"

class DamageBrick : public GameObject {
public:
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	DamageBrick();
};