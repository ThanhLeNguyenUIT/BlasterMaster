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
		boundingBox.left = x;
		boundingBox.top = y;
		boundingBox.right = x + 176;
		boundingBox.left = y + 176;
		movingObjects.clear();
		staticObjects.clear();
	}
	RECT GetBbox() { return boundingBox; }
	~Cell() {}
};