#pragma once
#include "GameObject.h"

/*
	Object that triggers scene switching
*/
class Portal : public GameObject
{
public:
	Portal();
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	int GetSceneId() { return scene_id; }
};