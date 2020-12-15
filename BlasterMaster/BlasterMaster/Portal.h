#pragma once
#include "GameObject.h"

/*
	Object that triggers scene switching
*/
class Portal : public GameObject
{
	int width;
	int height;
public:
	int scene_id;	// target scene to switch to 
	Portal(float l, float t, float r, float b, int scene_id);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	int GetSceneId() { return scene_id; }
};