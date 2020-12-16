#pragma once
#include "GameObject.h"
#include <unordered_set>
class Cell
{
public:
	int posX, posY;
	RECT boundingBox;
	unordered_set<LPGAMEOBJECT> movingObjects;
	unordered_set<LPGAMEOBJECT> staticObjects;
	Cell(int x, int y)
	{
		this->posX = x;
		this->posY = y;
		movingObjects.clear();
		staticObjects.clear();
	}
	RECT GetBbox() { return boundingBox; }
	~Cell() {}
};