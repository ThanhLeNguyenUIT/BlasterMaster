#include "Teleporters.h"
#include <cstdlib>
#include <ctime>



void Teleporter::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 24;
	bottom = y + 32;
}

void Teleporter::ChangeAnimation(STATEOBJECT StateObject) {
	this->StateObject = StateObject;
	AnimationSets* animation_sets = AnimationSets::GetInstance();
	LPANIMATION_SET animationSet = animation_sets->Get(typeTeleporter);
	CurAnimation = animationSet->Get(this->StateObject);

}

void Teleporter::Render() {
	//Reset();
	int alpha = 255;
	CurAnimation->Render(x, y, alpha);
	RenderBoundingBox();
}

void Teleporter::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {


	GameObject::Update(dt, coObjects);
	//ChangeAnimation(GOOMBA_MOVE);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	//if (coEvents.size() == 0)
	//{
	DWORD timenow = GetTickCount();
	if ((timenow - dt) % 200 == 0) {
		if (nx > 0) {
			ChangeAnimation(TELEPORTERS_IDLE);
			nx = -1;
			//DebugOut(L"TELEPORTER IDLE");
		}
		else if (nx < 0) {
			ChangeAnimation(TELEPORTERS_MOVE);
			nx = 1;
			//DebugOut(L"TELEPORTER MOVE");
			DWORD timenow1 = GetTickCount();
			int n = rand() % (93 - 82 + 1) + 82;
			int m = rand() % (69 - 63 + 1) + 63;
			SetPosition(n * BIT, m * BIT);	
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


