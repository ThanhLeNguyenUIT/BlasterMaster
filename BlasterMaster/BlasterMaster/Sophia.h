#pragma once
#include "GameObject.h"
#include "PlayerState.h"
#include "Enemy.h"
#include "EnemyBullet.h"
#include "Item.h"
#include "PlayerBullet.h"


class Sophia : public GameObject
{
public:
	PlayerBullet* bullet;
	float oldCx, oldCy;
	int old_scene_id = 0;
	static Sophia* _instance;
	int stateBoundingBox;
	PlayerState* state;
	Animation* CurAnimation;
	D3DCOLOR color;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* staticObject, vector<Enemy*>* coEnemy, vector<Item*>* coItem, vector<EnemyBullet*>* coBullet);
	virtual void Render();
	bool IsJumping = false;
	bool IsOnGround;
	bool IsWalking;
	bool IsStop;
	bool IsLoad = true;
	bool IsFiring = false;
	bool IsDead = false;
	bool IsUp = false;
	bool IsTouchPortal;
	bool IsRender = true;
	bool IsTouchStair;
	bool IsUntouchable = false;
	bool IsOpen = false;
	bool IsMoving = false;
	bool IsDamaged = false;
	//bool IsLoad = false;
	bool IsChangeScene = false;
	DWORD timeStartAttack = TIME_DEFAULT;
	DWORD timeDamaged = TIME_DEFAULT;
	int count = 0;
	int countColor = 0;
	int idFrame = 0;
	bool RenderOneFrame = false;
	bool RenderBack = false;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	Sophia();
	~Sophia();
	void Fire();
	void SetPlayerType(TYPE playerType) { this->type = playerType; }
	void ChangeAnimation(PlayerState* state, int stateChange = 0);
	void ChangeScene();
	static Sophia* GetInstance();
	void CheckState(int stateChange);
	void Reset(float x = 67 * BIT, float y = 72 * BIT);
	void OnKeyUp(int key);
	void OnKeyDown(int key);
	int randomAlpha() {
		for (int i = 150; i < 180; i++)
			return  (rand() % 180) + 1;
	}
	int randomG() {
		for (int i = 100; i < 150; i++)
			return  (rand() % 150) + 1;
	}
	int randomB() {
		for (int i = 100; i < 150; i++)
			return  (rand() % 150) + 1;
	}
};

