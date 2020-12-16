#pragma once 
#include "GameObject.h"

class Stair : public GameObject
{
public:
	Stair();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Render();
};


