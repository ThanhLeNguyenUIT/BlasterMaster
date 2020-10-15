#pragma once
#include "GameObject.h"
#include "Bullet.h"

#define CAR_MOVING_SPEED             0.1f
#define CAR_JUMP_SPEED_Y             0.8f
#define CAR_GRAVITY                  0.001f
#define CAR_JUMP_DEFLECT_SPEED     0.2f
#define CAR_DIE_DEFLECT_SPEED	   0.5f



class PlayerState;
class CGameObject;

class CCar : public CGameObject
{
	CBullet* bullet ;
	vector<CBullet*> bullets;
	
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
	bool IsWalking;
	bool IsStop;
	bool IsFiring;
	bool IsDead;
	bool IsUp;
	bool rev;
	int idFrame = 0;
	bool renderOneFrame = false;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Revival();

	CCar();
	~CCar();
	void ChangeAnimation(PlayerState* state, int stateId = 0);
	static CCar* GetInstance();
	void AddBullet();
	void DeleteBullet();
	void OnKeyUp(int key);
	void OnKeyDown(int key);
};

