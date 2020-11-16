#include <d3dx9.h>
#include <algorithm>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Sprites.h"
#include "Textures.h"



GameObject::GameObject(){
	x = y = 0;
	vx = vy = 0;
	nx = 1;
}

void GameObject::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	this->dt = dt;
	dx = vx * dt;
	dy = vy * dt;
}

LPCOLLISIONEVENT GameObject::SweptAABBEx(LPGAMEOBJECT coO)    //
{
	float sl, st, sr, sb;		// position static object bbox
	float ml, mt, mr, mb;		// position moving object bbox
	float t, nx, ny;

	coO->GetBoundingBox(sl, st, sr, sb);

	// deal with moving object: m speed = original m speed - collide object speed
	float svx, svy;
	coO->GetSpeed(svx, svy);

	float sdx = svx * dt;     //quang duong di duoc trong 1 khoang dt theo chieu x
	float sdy = svy * dt;	  //quang duong di duoc trong 1 khoang dt theo chieu y

	float dx = this->dx - sdx;  //cap nhat lai dx
	float dy = this->dy - sdy;	//cap nhat lai dy

	GetBoundingBox(ml, mt, mr, mb);

	Game::SweptAABB(
		ml, mt, mr, mb,
		dx, dy,
		sl, st, sr, sb,
		t, nx, ny
	);    // tinh nx, ny ,t

	CollisionEvent* e = new CollisionEvent(t, nx, ny, coO);  
	return e;
}

void GameObject::CalcPotentialCollisions(   // tính các va chạm có khả năng xảy ra trong frame tới
	vector<LPGAMEOBJECT>* coObjects,
	vector<LPCOLLISIONEVENT>& coEvents)
{
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i));

		if (e->t > 0 && e->t <= 1.0f)  // chuan bi va cham
			coEvents.push_back(e);
		else
			delete e;
	}

	std::sort(coEvents.begin(), coEvents.end(), CollisionEvent::compare); // sap xep theo va cham theo thoi gian xay ra nhanh nhat
}

void GameObject::FilterCollision(   //lọc va chạm tìm sự kiện gần xảy ra nhất theo chiều x và chiều y
	vector<LPCOLLISIONEVENT>& coEvents,
	vector<LPCOLLISIONEVENT>& coEventsResult,
	float& min_tx, float& min_ty,
	float& nx, float& ny)
{
	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	nx = 0.0f;
	ny = 0.0f;

	coEventsResult.clear();

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT c = coEvents[i];

		if (c->t < min_tx && c->nx != 0) {
			min_tx = c->t; nx = c->nx; min_ix = i;
		}

		if (c->t < min_ty && c->ny != 0) {
			min_ty = c->t; ny = c->ny; min_iy = i;
		}
	}

	if (min_ix >= 0) coEventsResult.push_back(coEvents[min_ix]);
	if (min_iy >= 0) coEventsResult.push_back(coEvents[min_iy]);
}


void GameObject::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPDIRECT3DTEXTURE9 bbox = Textures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;
	//DebugOut(L"RenderBoundingBox: %d\n" );
	Game::GetInstance()->Draw(l, t, bbox, rect.left, rect.top, rect.right, rect.bottom, 80);
}

GameObject::~GameObject(){
}
		
