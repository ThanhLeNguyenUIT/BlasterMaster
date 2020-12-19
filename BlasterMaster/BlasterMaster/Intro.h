#pragma once
#include "GameObject.h"




class CIntro : public GameObject
{


public:
	TYPE typeScene;
	Animation* CurAnimation;
	CIntro(float x = 0.0f, float y = 0.0f);
	STATEOBJECT StateObject;
	void ChangeAnimation(STATEOBJECT StateObject);
	STATEOBJECT GetStateObject() { return this->StateObject; }
	void SetType(TYPE type) { this->typeScene = type; }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void Reset();
};
