#include "Goomba.h"


void Goomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 22;
	bottom = y + 27;
}

void Goomba::ChangeAnimation(STATEOBJECT StateObject) {
	this->StateObject = StateObject;
	AnimationSets* animation_sets = AnimationSets::GetInstance();
	LPANIMATION_SET animationSet = animation_sets->Get(typeCanon);
	CurAnimation = animationSet->Get(this->StateObject);

}

void Goomba::Render() {
	Reset();
	int alpha = 255;		
	CurAnimation->Render(x, y, alpha);
	RenderBoundingBox();
}

void Goomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {


	GameObject::Update(dt, coObjects);
	//ChangeAnimation(GOOMBA_MOVE);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else {
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx * dx + nx * 0.1f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;



		//for (int i = 0; i < coEvents.size(); i++)
		//{
		//	LPCOLLISIONEVENT e = coEventsResult[i];
		//	if (dynamic_cast<Brick*>(e->obj)) {
		//		if (nx != 0) ChangeAnimation(BULLET_SMALL_HIT);
		//		if (ny != 0) ChangeAnimation(BULLET_SMALL_HIT);
		//		//isDead = true;
		//	}

		//	else if (dynamic_cast<Portal*>(e->obj)) {
		//		if (nx != 0) ChangeAnimation(BULLET_SMALL_HIT);
		//		if (ny != 0) ChangeAnimation(BULLET_SMALL_HIT);
		//		//isDead = true;
		//	}

		//	else if (dynamic_cast<Bullet*>(e->obj)) {
		//		//isDead = true;
		//		/*if (nx != 0) ChangeAnimation(BULLET_SMALL_HIT);
		//		if (ny != 0) ChangeAnimation(BULLET_SMALL_HIT);*/
		//	}
		//}

		//for (int i = 0; i < coEvents.size(); i++) {
		//	delete coEvents[i];
		//}

		// Collision logic with Goombas
		//for (UINT i = 0; i < coEventsResult.size(); i++)
		//{
		//	LPCOLLISIONEVENT e = coEventsResult[i];ob

		//	if (dynamic_cast<CGoomba*>(e->obj)) // if e->obj is Goomba 
		//	{
		//		CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
		//		
		//		// jump on top >> kill Goomba and deflect a bit 
		//		if (e->nx < 0 || e->nx > 0)
		//		{
		//			if (goomba->GetState() != GOOMBA_STATE_DIE)
		//			{
		//				goomba->SetState(GOOMBA_STATE_DIE);
		//				state = BULLET_STATE_HIT;
		//			}
		//		}
		//	}
		//}
	}
}

void Goomba::Reset(float x, float y) {
	nx = 1;
	SetPosition(x, y);
	ChangeAnimation(GOOMBA_NORMAL);
	SetSpeed(0, 0);
}

