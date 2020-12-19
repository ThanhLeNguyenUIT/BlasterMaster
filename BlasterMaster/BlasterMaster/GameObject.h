#pragma once
#include "GlobalConfig.h"
#include "Animations.h"
#include "Sprites.h"

#include <Windows.h>
#include <d3dx9.h>
#include <vector>

using namespace std;

#define ID_TEX_BBOX -100		// special texture to draw object bounding box
#define ID_TEX_MAP 50

class GameObject;
typedef GameObject* LPGAMEOBJECT;
class Animation;
struct CollisionEvent;
typedef CollisionEvent* LPCOLLISIONEVENT;
struct CollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;
	CollisionEvent(float t, float nx, float ny, LPGAMEOBJECT obj = NULL) { this->t = t; this->nx = nx; this->ny = ny; this->obj = obj; }

	static bool compare(const LPCOLLISIONEVENT& a, LPCOLLISIONEVENT& b)
	{
		return a->t < b->t;
	}
};



class GameObject
{
public:

	float x;
	float y;

	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt

	float vx;
	float vy;

	int nx;
	int ny;

	float width;
	float height;
	int scene_id;
	int health = 0;
	DWORD timeStartCol = TIME_DEFAULT;
	int state;
	DWORD dt;
	TYPE type;
	STATENAME StateName;
	STATEOBJECT StateObject;
	LPANIMATION_SET animation_set;

	bool isDead = false;
public:
	RECT GetRect();
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSize(float width = 0, float height = 0) { this->width = width, this->height = height; }
	void SetSceneId(int id = 0) { this->scene_id = id; }
	void SetType(TYPE type) { this->type = type; }
	TYPE GetType() { return this->type; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetPosition(float& x, float& y) { x = this->x; y = this->y; }
	void GetSpeed(float& vx, float& vy) { vx = this->vx; vy = this->vy; }
	STATEOBJECT GetStateObject() { return this->StateObject; }
	STATENAME GetStateName() { return this->StateName; }
	float GetX() { return this->x; }
	float GetY() { return this->y; }
	int GetState() { return this->state; }

	void RenderBoundingBox();
	bool CollisionWithObject(GameObject* obj);
	void SetAnimationSet(LPANIMATION_SET ani_set) { animation_set = ani_set; }

	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT>* coObjects, vector<LPCOLLISIONEVENT>& coEvents);
	void FilterCollision(
		vector<LPCOLLISIONEVENT>& coEvents,
		vector<LPCOLLISIONEVENT>& coEventsResult,
		float& min_tx,
		float& min_ty,
		float& nx,
		float& ny);

	GameObject();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render() = 0;
	virtual void SetState(int state) { this->state = state; }

	~GameObject();
};

