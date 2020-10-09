#pragma once
#include "GameObject.h"
#include "Bullet.h"

#define CAR_MOVING_SPEED             0.2f
#define CAR_JUMP_SPEED_Y             0.5f
#define CAR_GRAVITY                  0.002f
#define CAR_JUMP_DEFLECT_SPEED     0.2f
#define CAR_DIE_DEFLECT_SPEED	   0.5f

//#define CAR_STATE_IDLE              0
//#define CAR_STATE_MOVING_RIGHT      100
//#define CAR_STATE_MOVING_LEFT       200
//#define CAR_STATE_JUMP_RIGHT        300
//#define CAR_STATE_JUMP_LEFT			400
//#define CAR_STATE_JUMP              500
//#define CAR_STATE_FIRE				600
//#define CAR_STATE_NOT_FIRE			700

#define CAR_ANI_IDLE_RIGHT		0
#define CAR_ANI_IDLE_LEFT		1
#define CAR_ANI_MOVING_RIGHT	2
#define CAR_ANI_MOVING_LEFT		3

#define CAR_STATE_DIE       4



class PlayerState;
class CGameObject;

class CCar : public CGameObject
{
	CBullet* bullet ;
	vector<CBullet*> bullets;
	void AddBullet();
	void DeleteBullet();
	
private:
	static CCar* _instance;
public:
	int stateBoundingBox;
	PlayerState* state;
	CAnimation* CurAnimation;
	std::unordered_map<STATENAME, bool> allow;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	//bool IsJumping() { return this->isJumping; }
	bool IsJumping;
	bool IsOnGround;
	bool IsFiring;
	bool IsDead;
	bool IsUp;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Revival();

	CCar();
	~CCar();
	void ChangeAnimation(PlayerState* state);
	static CCar* GetInstance();
	void OnKeyUp(int key);
	void OnKeyDown(int key);
};

