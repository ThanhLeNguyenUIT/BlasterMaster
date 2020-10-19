#include "Bullet.h"
#include "Goomba.h"

void Bullet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + BULLET_SMALL_BBOX_WIDTH;
	bottom = y + BULLET_SMALL_BBOX_HEIGHT;
}

void Bullet::Render() {
	int ani;
	if (state == BULLET_STATE_MOVING_RIGHT) {
		ani = SOPHIA_BULLET_SMALL_ANI_RIGHT;
	}
	else if (state == BULLET_STATE_MOVING_LEFT) {
		ani = SOPHIA_BULLET_SMALL_ANI_LEFT;
	}
	else if (state == BULLET_STATE_MOVING_UP) {
		ani = SOPHIA_BULLET_SMALL_ANI_UP;
	}
	else if (state == BULLET_STATE_HIT) {
		ani = SOPHIA_BULLET_ANI_HIT;
	}
	animation_set->at(ani)->Render(x, y);
	//RenderBoundingBox();
}

void Bullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	GameObject::Update(dt, coObjects);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	//x += dx;

	// turn off collision when bullet hit 
	if (state != BULLET_STATE_HIT) {
		CalcPotentialCollisions(coObjects, coEvents);
	}

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else {
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		
		// block 
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) state = BULLET_STATE_HIT;
		if (ny != 0) vy = 0;
		
		// Collision logic with Goombas
		//for (UINT i = 0; i < coEventsResult.size(); i++)
		//{
		//	LPCOLLISIONEVENT e = coEventsResult[i];

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

void Bullet::SetState(int state) {
	GameObject::SetState(state);
	switch (state) {
	case BULLET_STATE_MOVING_RIGHT:
		vx = BULLET_MOVING_SPEED;
		break;
	case BULLET_STATE_MOVING_LEFT:
		vx = -BULLET_MOVING_SPEED;
		break;
	case BULLET_STATE_MOVING_UP:
		vy = -BULLET_MOVING_SPEED;
		break;
	case BULLET_STATE_HIT:
		vx = 0;
		vy = 0;
		break;
	}
}
