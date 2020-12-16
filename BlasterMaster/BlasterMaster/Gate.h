#pragma once
#include "GameObject.h"

class Gate : public GameObject
{
public:
	Gate();
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	int GetSceneId() { return scene_id; }
};