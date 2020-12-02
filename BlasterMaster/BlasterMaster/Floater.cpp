#include "Floater.h"
#include "Brick.h"
#include "Portal.h"
#include "Power.h"
#include "DamageBrick.h"
#include "EnemyBullet.h"

CFloater::CFloater(float x, float y)
{
	this->x = x;
	this->y = y;
	typeEnemy = FLOATER;
	Reset();
}

void CFloater::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + FLOATER_BBOX_WIDTH;
	bottom = y + FLOATER_BBOX_HEIGHT;
}

void CFloater::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);

	
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (health == 0) {
		StateObject = ENEMY_DEAD;
	}

	// turn off collision when die 
	if (StateObject != ENEMY_DEAD)
		CalcPotentialCollisions(coObjects, coEvents);
	// fire and delete bullet
	Fire();
	for (int i = 0; i < listBullets.size(); i++) {
		listBullets[i]->Update(dt, coObjects);
	}

	for (int i = 0; i < listBullets.size(); i++) {
		if (listBullets[i]->GetStateObject() == BULLET_SMALL_HIT) {
			if (GetTickCount() - listBullets[i]->timeStartCol >= BULLET_TIME_EXPLOSIVE && listBullets[i]->timeStartCol != TIME_DEFAULT) {
				listBullets.erase(listBullets.begin() + i);
			}
		}
	}

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block every object first!
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		//
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<Brick*>(e->obj)) // if e->obj is Brick
			{
				if (e->ny > 0 && e->nx == 0)
				{
					if (this->vx > 0)
					{
						ChangeAnimation(FLOATER_STATE_WALKING_RIGHT_BOTTOM);
					}
					else if (this->vx < 0)
					{
						ChangeAnimation(FLOATER_STATE_WALKING_LEFT_BOTTOM);
					}
				}
				else if (e->ny < 0 && e->nx == 0)
				{
					if (this->vx > 0)
					{
						ChangeAnimation(FLOATER_STATE_WALKING_RIGHT_TOP);
					}
					else if (this->vx < 0)
					{
						ChangeAnimation(FLOATER_STATE_WALKING_LEFT_TOP);
					}
				}
				else if (e->nx > 0 && e->ny == 0)
				{
					if (this->vy > 0)
					{
						ChangeAnimation(FLOATER_STATE_WALKING_RIGHT_BOTTOM);
					}
					else if (this->vy < 0)
					{
						ChangeAnimation(FLOATER_STATE_WALKING_RIGHT_TOP);
					}
				}
				else if (e->nx < 0 && e->ny == 0)
				{
					if (this->vy > 0)
					{
						ChangeAnimation(FLOATER_STATE_WALKING_LEFT_BOTTOM);
					}
					else if (this->vy < 0)
					{
						ChangeAnimation(FLOATER_STATE_WALKING_LEFT_TOP);
					}
				}

			}
			if (dynamic_cast<DamageBrick*>(e->obj)){ // if e->obj is Brick
				if (e->ny > 0 && e->nx == 0)
				{
					if (this->vx > 0)
					{
						ChangeAnimation(FLOATER_STATE_WALKING_RIGHT_BOTTOM);
					}
					else if (this->vx < 0)
					{
						ChangeAnimation(FLOATER_STATE_WALKING_LEFT_BOTTOM);
					}
				}
				else if (e->ny < 0 && e->nx == 0)
				{
					if (this->vx > 0)
					{
						ChangeAnimation(FLOATER_STATE_WALKING_RIGHT_TOP);
					}
					else if (this->vx < 0)
					{
						ChangeAnimation(FLOATER_STATE_WALKING_LEFT_TOP);
					}
				}
				else if (e->nx > 0 && e->ny == 0)
				{
					if (this->vy > 0)
					{
						ChangeAnimation(FLOATER_STATE_WALKING_RIGHT_BOTTOM);
					}
					else if (this->vy < 0)
					{
						ChangeAnimation(FLOATER_STATE_WALKING_RIGHT_TOP);
					}
				}
				else if (e->nx < 0 && e->ny == 0)
				{
					if (this->vy > 0)
					{
						ChangeAnimation(FLOATER_STATE_WALKING_LEFT_BOTTOM);
					}
					else if (this->vy < 0)
					{
						ChangeAnimation(FLOATER_STATE_WALKING_LEFT_TOP);
					}
				}
			}
			if (dynamic_cast<Portal*>(e->obj))
			{
				Portal* p = dynamic_cast<Portal*>(e->obj);
				if (e->ny > 0 && e->nx == 0)
				{
					if (this->vx > 0)
					{
						ChangeAnimation(FLOATER_STATE_WALKING_RIGHT_BOTTOM);
					}
					else if (this->vx < 0)
					{
						ChangeAnimation(FLOATER_STATE_WALKING_LEFT_BOTTOM);
					}
				}
				else if (e->ny < 0 && e->nx == 0)
				{
					if (this->vx > 0)
					{
						ChangeAnimation(FLOATER_STATE_WALKING_RIGHT_TOP);
					}
					else if (this->vx < 0)
					{
						ChangeAnimation(FLOATER_STATE_WALKING_LEFT_TOP);
					}
				}
				else if (e->nx > 0 && e->ny == 0)
				{
					if (this->vy > 0)
					{
						ChangeAnimation(FLOATER_STATE_WALKING_RIGHT_BOTTOM);
					}
					else if (this->vy < 0)
					{
						ChangeAnimation(FLOATER_STATE_WALKING_RIGHT_TOP);
					}
				}
				else if (e->nx < 0 && e->ny == 0)
				{
					if (this->vy > 0)
					{
						ChangeAnimation(FLOATER_STATE_WALKING_LEFT_BOTTOM);
					}
					else if (this->vy < 0)
					{
						ChangeAnimation(FLOATER_STATE_WALKING_LEFT_TOP);
					}
				}
			}
			if (dynamic_cast<Enemy*>(e->obj)) {
				if (e->nx != 0) x += dx;
				if (e->ny != 0) y += dy;
			}
			if (dynamic_cast<Power*>(e->obj)) {
				if (e->nx != 0) x += dx;
				if (e->ny != 0)y += dy;
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CFloater::Render()
{
	int alpha = 255;
	CurAnimation->Render(x, y, alpha);

	for (int i = 0; i < listBullets.size(); i++) {
		listBullets[i]->Render();
	}
	
	//RenderBoundingBox();
}

void CFloater::ChangeAnimation(STATEOBJECT StateObject) {
	this->StateObject = StateObject;
	AnimationSets* animation_sets = AnimationSets::GetInstance();
	LPANIMATION_SET animationSet = animation_sets->Get(typeEnemy);
	CurAnimation = animationSet->Get(this->StateObject);
	switch (this->StateObject)
	{
	case FLOATER_STATE_WALKING_RIGHT_TOP:
		vx = FLOATER_WALKING_SPEED_X;
		vy = -FLOATER_WALKING_SPEED_Y;
		break;
	case FLOATER_STATE_WALKING_LEFT_TOP:
		vx = -FLOATER_WALKING_SPEED_X;
		vy = -FLOATER_WALKING_SPEED_Y;
		break;
	case FLOATER_STATE_WALKING_RIGHT_BOTTOM:
		vx = FLOATER_WALKING_SPEED_X;
		vy = FLOATER_WALKING_SPEED_Y;
		break;
	case FLOATER_STATE_WALKING_LEFT_BOTTOM:
		vx = -FLOATER_WALKING_SPEED_X;
		vy = FLOATER_WALKING_SPEED_Y;
		break;
	}
}

void CFloater::Reset() {
	nx = 1;
	ChangeAnimation(FLOATER_STATE_WALKING_LEFT_BOTTOM);
}

void CFloater::Fire() {
	if (timeStartAttack == TIME_DEFAULT) {
		timeStartAttack = GetTickCount();
	}
	if (GetTickCount() - timeStartAttack >= 2000 && timeStartAttack!=TIME_DEFAULT) {
		bullet = new EnemyBullet();
		bullet->typeBullet = ENEMY_BULLET;
		if (nx > 0) {
			bullet->SetPosition(x + FLOATER_BBOX_WIDTH / 4, y + FLOATER_BBOX_HEIGHT / 3);
			bullet->ChangeAnimation(ENEMY_BULLET_SMALL_MOVING);
		}
		else {
			bullet->SetPosition(x + FLOATER_BBOX_WIDTH / 4, y + FLOATER_BBOX_HEIGHT / 3);
			bullet->ChangeAnimation(ENEMY_BULLET_SMALL_MOVING);
		}
		listBullets.push_back(bullet);
		timeStartAttack = GetTickCount();
	}
}

