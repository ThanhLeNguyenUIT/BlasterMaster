#pragma once
#pragma once
#include "GameObject.h"
#include "PlayerState.h"
#include "PlayerBullet.h"
#include "EnemyBullet.h"
#include "Item.h"
#include "Enemy.h"

class BigJason : public GameObject
{
public:
	bool doneFlash;
	PlayerBullet* bullet;
	vector<int> sceneHistory = { 11 };
	int scene_gate;
	static BigJason* _instance;
	int stateBoundingBox;
	PlayerState* state;
	Animation* CurAnimation;
	std::unordered_map<TYPE, bool> allow;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects, vector<Enemy*>* coEnemy, vector<Item*>* coItem, vector<EnemyBullet*>* coBullet);
	virtual void Render();
	DWORD timeStartAttack = TIME_DEFAULT;
	DWORD timeDamaged = TIME_DEFAULT;
	D3DCOLOR color;
	bool IsTouchPortal;
	bool IsJumping;
	bool IsOnGround;
	bool IsMoving;
	bool IsStop;
	bool IsCrawling = false;
	bool IsFiring = false;
	bool IsDead;
	bool IsUp;
	bool IsTouchGate = false;
	bool IsChangeScene = false;
	bool IsUntouchable = false;
	bool IsOpen = false;
	bool IsRender;
	bool IsDamaged = false;
	//bool IsLoad = true;
	bool RenderOneFrame = false;
	bool rev;
	int count = 0;
	int countColor = 0;
	int idFrame = 0;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	BigJason();
	~BigJason();
	void SetPlayerType(TYPE playerType) { this->type = playerType; }
	void ChangeAnimation(PlayerState* state, int stateChange = 0);
	void ChangeScene(int sceneId);
	static BigJason* GetInstance();
	void Reset(float x = 384, float y = 112);
	void OnKeyUp(int key);
	void OnKeyDown(int key);
};

