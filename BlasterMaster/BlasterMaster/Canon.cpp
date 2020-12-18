#include "Canon.h"


void Canon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}

void Canon::ChangeAnimation(STATEOBJECT StateObject) {
	this->StateObject = StateObject;
	AnimationSets* animation_sets = AnimationSets::GetInstance();
	LPANIMATION_SET animationSet = animation_sets->Get(type);
	CurAnimation = animationSet->Get(this->StateObject);
}

void Canon::Render() {
	int alpha = 255;
	CurAnimation->Render(x, y, alpha);
	RenderBoundingBox();
}

void Canon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {


	GameObject::Update(dt, coObjects);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (health <= 0) {
		StateObject = ENEMY_DEAD;
		isDead = true;
	}
	if(timenow == TIME_DEFAULT)
		timenow = GetTickCount();

	if (GetTickCount() - timenow >= 250) {
		if (nx > 0) {
			ChangeAnimation(CANON_NORMAL);
			nx = -1;
			Fire();
		}
		else if (nx < 0) {
			ChangeAnimation(CANON_MOVING);
			nx = 1;
			Fire();
		}
		timenow = TIME_DEFAULT;
	}
}

void Canon::Fire() {
		if (nx < 0 && CurAnimation->currentFrame == 1) {
			bullet1 = new EnemyBullet();
			bullet2 = new EnemyBullet();
			bullet1->type = ENEMY_BULLET;
			bullet2->type = ENEMY_BULLET;
			bullet1->SetPosition(x + CANON_BBOX_WIDTH , y + CANON_BBOX_HEIGHT / 3);
			bullet1->ChangeAnimation(CANON_BULLET_MOVING_RIGHT);
			bullet2->SetPosition(x , y + CANON_BBOX_HEIGHT / 3);
			bullet2->ChangeAnimation(CANON_BULLET_MOVING_LEFT);
			IsFiring = true;
		}
		else if (nx > 0 && CurAnimation->currentFrame == 0) {
			bullet3 = new EnemyBullet();
			bullet4 = new EnemyBullet();
			bullet3->type = ENEMY_BULLET;
			bullet4->type = ENEMY_BULLET;
			bullet3->SetPosition(x + CANON_BBOX_WIDTH / 3, y);
			bullet3->ChangeAnimation(CANON_BULLET_MOVING_UP);
			bullet4->SetPosition(x + CANON_BBOX_WIDTH / 3, y + CANON_BBOX_HEIGHT);
			bullet4->ChangeAnimation(CANON_BULLET_MOVING_DOWN);
			IsFiring = true;
		}
}


