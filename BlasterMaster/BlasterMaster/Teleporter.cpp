#include "Teleporter.h"
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
	LPANIMATION_SET animationSet = animation_sets->Get(type);
	CurAnimation = animationSet->Get(this->StateObject);

}

void Teleporter::Render() {
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
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (health == 0) {
		StateObject = ENEMY_DEAD;
		isDead = true;
	}

	DWORD timenow = GetTickCount();
	int random = rand() % 2;
	if (random == 1) {
		if ((timenow - dt) % 1000 == 0) {
			ChangeAnimation(TELEPORTERS_IDLE);
			nx = -1;
		}
	}
	else if (random != 1) {
		if ((timenow - dt) % 500 == 0) {
			ChangeAnimation(TELEPORTERS_MOVE);
			nx = 1;
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
		}
	}
}




