#include "Teleporters.h"
#include <cstdlib>
#include <ctime>

#define limitX (startX + 6) * BIT
#define limitY (startY + 6) * BIT

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
	int ran = rand() % 10;
	int alpha = 255;
	if (this->StateObject == TELEPORTERS_MOVE) {
		alpha = ran < 7 ? 255 : 0;
	}
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
	int random = rand() % 2;
	if (random == 1) {
		if ((timenow - dt) % 1000 == 0) {
			ChangeAnimation(TELEPORTERS_IDLE);
			nx = -1;
			//DebugOut(L"TELEPORTER IDLE");
		}
	}
	else if (random != 1) {
		if ((timenow - dt) % 500 == 0) {
			ChangeAnimation(TELEPORTERS_MOVE);
			nx = 1;
			//DebugOut(L"TELEPORTER MOVE");
			//DWORD timenow1 = GetTickCount();
			///////////////////////////////////////
			//int a = rand() % 4;
			//int prevA = a;
			//while (prevA == a) {
			//	a = rand() % 4;
			//}
			//prevA = a;
			//DebugOut(L"%d\n", a);
			//int distance = rand() % 50;
			//a == 0 
			//	? SetPosition(startX + distance, startY + distance)
			//	: (a == 1)
			//	? SetPosition(startX - distance, startY + distance)
			//	: (a == 2)
			//	? SetPosition(startX + distance + rand() % 20, startY - distance - rand() % 20)
			//	: SetPosition(startX - distance - rand() % 20, startY - distance - rand() % 20);
			///////////////////////////////////////
			int a = rand() % 2; // x = 0, y = 1
			int b = rand() % 2; // + = 0, - = 1
			int distance = 35;
			if (a == 0) {
				if (b == 0) {
					if (x + distance > startX - 6) {
						SetPosition(x - distance, y);
					}
				}
				else if (b == 1) {
					if (x - distance < startX + 6) {
						SetPosition(x + distance, y);
					}
				}
			}
			else if (a == 1) {
				if (b == 0) {
					if (y + distance > startY + 6) {
						SetPosition(x, y - distance);
					}
				}
				else if (b == 1) {
					if (y - distance < startY - 6) {
						SetPosition(x, y + distance);
					}
				}
			}

			///////////////////////////////////////
			/*int n = rand() % (93 - 82 + 1) + 82;
			int m = rand() % (69 - 63 + 1) + 63;*/
			/*SetPosition(n * BIT, m * BIT);	*/
		}
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



