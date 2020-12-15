#include "Canon.h"


void Canon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 26;
	bottom = y + 26;
}

void Canon::ChangeAnimation(STATEOBJECT StateObject) {
	this->StateObject = StateObject;
	AnimationSets* animation_sets = AnimationSets::GetInstance();
	LPANIMATION_SET animationSet = animation_sets->Get(typeCanon);
	CurAnimation = animationSet->Get(this->StateObject);

}

void Canon::Render() {
	//Reset();
	int alpha = 255;
	CurAnimation->Render(x, y, alpha);
	RenderBoundingBox();
}

void Canon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {


	GameObject::Update(dt, coObjects);
	//ChangeAnimation(GOOMBA_MOVE);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	//if (coEvents.size() == 0)
	//{
	DWORD timenow = GetTickCount();
	if ((timenow - dt) % 500 == 0) {
		if (nx > 0) {
			ChangeAnimation(CANON_NORMAL);
			nx = -1;
			//DebugOut(L"canon moving");
		}
		else if (nx < 0) {
			ChangeAnimation(CANON_MOVING);
			nx = 1;
			//DebugOut(L"canon normal");
		}
	}
	
	//}
	//else {
	//	float min_tx, min_ty, nx = 0, ny;

	//	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

	//	// block 
	//	x += min_tx * dx + nx * 0.1f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
	//	y += min_ty * dy + ny * 0.4f;
	//	
	//}
}


