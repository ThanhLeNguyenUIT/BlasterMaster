#include "Boss.h"
#include "Brick.h"
#include "Portal.h"
#include "Power.h"
#include "DamageBrick.h"
#include "GlobalConfig.h"

#include <ctime>
#define BOSS_WALKING_SPEED_X 0.03f
#define BOSS_WALKING_SPEED_Y 0.03f
#define BOSS_MAX_TOP 67*BIT
#define BOSS_MAX_LEFT 113*BIT
#define BOSS_MAX_BOTTOM 68*BIT
#define BOSS_MAX_RIGHT 125*BIT

CBoss* CBoss::_instance = NULL;


CBoss* CBoss::GetInstance() {
	if (_instance == NULL) {
		_instance = new CBoss();
	}
	return _instance;
}

CBoss::CBoss(float x, float y)
{
	type = BOSS;
	Reset();
	this->x = x;
	this->y = y;
	CBossArm* arm = new CBossArm(116 * BIT - 6, 66 * BIT, 1, 0.031, 0.031);
	listBossArm.push_back(arm);

	for (int i = 1; i < 4; i++)
	{
		CBossArm* arm = new CBossArm(116 * BIT - 6, 66 * BIT, 1, 0.027 + 0.0035 * (i + 1), 0.027 + 0.0035 * (i + 1));
		listBossArm.push_back(arm);
	}

	CBossArm* arm1 = new CBossArm(116 * BIT + 50, 66 * BIT, 2, 0.031, 0.031);
	listBossArm.push_back(arm1);


	for (int i = 1; i < 4; i++)
	{
		CBossArm* arm = new CBossArm(116 * BIT + 54, 66 * BIT, 2, 0.027 + 0.0035 * (i + 1), 0.027 + 0.0035 * (i + 1));
		listBossArm.push_back(arm);
	}
	float x_boss, y_boss;
	GetPosition(x_boss, y_boss);
	CBossHand* hand1 = new CBossHand(116 * BIT - 12, 66 * BIT + 20, 1, x_boss, y_boss);
	listBossHand.push_back(hand1);
	//DebugOut(L"succesful2");
	CBossHand* hand2 = new CBossHand(116 * BIT + 66, 66 * BIT + 20, 2, x_boss, y_boss);
	listBossHand.push_back(hand2);
	//DebugOut(L"succesful3");
}

void CBoss::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 60;
	bottom = y + 66;
}

void CBoss::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//DebugOut(L"x=%d, y=%t", this->x, this->y);
	if (isWakingUp && !isMoving) {
		SetSpeed(0, 0);
		for (int i = 0; i < listBossHand.size(); i++) {
			listBossHand[i]->SetSpeed(0, 0);
		}
		/*for (int i = 0; i < listBossArm.size(); i++) {
			listBossArm[i]->SetSpeed(0, 0);
		}*/
	}
	else {
		if (!isMoving) {
			SetSpeed(BOSS_WALKING_SPEED_X, BOSS_WALKING_SPEED_Y);
			listBossHand[0]->SetSpeed(BOSS_HAND_WALKING_SPEED_X, BOSS_HAND_WALKING_SPEED_Y);
			listBossHand[1]->SetSpeed(-BOSS_HAND_WALKING_SPEED_X, -BOSS_HAND_WALKING_SPEED_Y);
			/*for (int i = 0; i < listBossArm.size(); i++) {
				listBossArm[i]->SetSpeed(0, 0);
			}*/
			isMoving = true;
		}
	}
	
	GameObject::Update(dt, coObjects);


	//update boss
	if (x + 60 > BOSS_MAX_RIGHT) vx = -BOSS_WALKING_SPEED_X;
	if (y > BOSS_MAX_BOTTOM) vy = -BOSS_WALKING_SPEED_Y;
	if (x < BOSS_MAX_LEFT) vx = BOSS_WALKING_SPEED_X;
	if (y < BOSS_MAX_TOP) vy = BOSS_WALKING_SPEED_Y;

	//update hand
	for (int i = 0; i < listBossHand.size(); i++) {
		listBossHand[i]->SetBossPos(x, y);
		listBossHand[i]->Update(dt, coObjects);
	}

	//update tay
	float x_hand_left, y_hand_left, x_hand_right, y_hand_right;
	float x_diff_left, y_diff_left;
	float x_diff_right, y_diff_right;

	listBossHand[0]->GetPosition(x_hand_left, y_hand_left);


	listBossHand[1]->GetPosition(x_hand_right, y_hand_right);

	//listBossArm[0]->SetX(x + 6);
	//listBossArm[3]->SetXYFollow(x_hand_left, y_hand_left);


	x_diff_left = x_hand_left - x;
	y_diff_left = y_hand_left - y;
	listBossArm[0]->SetXYFollow(x - 6 + x_diff_left * 1 / 5, y + 6 + y_diff_left * 1 / 5);
	listBossArm[1]->SetXYFollow(x - 6 + x_diff_left * 2 / 5, y + 6 + y_diff_left * 2 / 5);
	listBossArm[2]->SetXYFollow(x - 6 + x_diff_left * 3 / 5, y + 6 + y_diff_left * 3 / 5);
	listBossArm[3]->SetXYFollow(x - 6 + x_diff_left * 4 / 5, y + 6 + y_diff_left * 4 / 5);



	x_diff_right = x_hand_right - (x + 50);
	y_diff_right = y_hand_right - y;

	listBossArm[4]->SetXYFollow(x + 50 + x_diff_right * 1 / 5, y + 6 + y_diff_right * 1 / 5);
	listBossArm[5]->SetXYFollow(x + 50 + x_diff_right * 2 / 5, y + 6 + y_diff_right * 2 / 5);
	listBossArm[6]->SetXYFollow(x + 50 + x_diff_right * 3 / 5, y + 6 + y_diff_right * 3 / 5);
	listBossArm[7]->SetXYFollow(x + 50 + x_diff_right * 4 / 5, y + 6 + y_diff_right * 4 / 5);

	/*listBossArm[4]->SetPosition(x + 50, y + 6);
	listBossArm[7]->SetXYFollow(x_hand_right, y_hand_right);
	listBossArm[6]->SetXYFollow(listBossArm[7]->GetX(), listBossArm[7]->GetY());
	listBossArm[5]->SetXYFollow(listBossArm[6]->GetX(), y_hand_right);*/

	for (int i = 0; i < listBossArm.size(); i++)
	{
		listBossArm[i]->Update(dt, coObjects);
	}


	//end update tay

	//handle collisions
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// dead
	if (healthBoss == 0) {
		isDead = true;
	}

	if (IsDamaged) {
		if (timeDamaged == TIME_DEFAULT) {
			timeDamaged = GetTickCount();
		}
		if (GetTickCount() - timeDamaged >= 600) {
			IsDamaged = false;
			timeDamaged = TIME_DEFAULT;
		}
	}

	// create bullet
	if (!isWakingUp && !isDead)
		Fire();
	// turn off collision when die 
	if (!isDead)
		CalcPotentialCollisions(coObjects, coEvents);

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
		}
	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

}

void CBoss::Render()
{
	int alpha = 255;
	/*if (isWakingUp) {
		alpha = rand() % 2 == 1 ? 50 : rand() % 2 == 1 ? 155 : 255;
	}*/
	
	D3DCOLOR colorOrange = D3DCOLOR_ARGB(alpha, 248, 120, 88);
	D3DCOLOR colorGreen = D3DCOLOR_ARGB(alpha, 0, 157, 64);
	D3DCOLOR colorGrey = D3DCOLOR_ARGB(alpha, 188, 186, 182);

	if (IsDamaged) {
		if (countColor == 0) {
			color = colorOrange;
			countColor++;
		}
		else if (countColor == 1) {
			color = colorGreen;
			countColor++;
		}
		else {
			color = colorGrey;
			countColor = 0;
		}
	}

	if (!isDead) {
		if(!IsDamaged)
			CurAnimation->Render(x, y, alpha);
		else 
			CurAnimation->Render(x, y, alpha, color);

		for (int i = 0; i < listBossArm.size(); i++)
		{
			listBossArm[i]->setAlpha(alpha);
			listBossArm[i]->Render();
		}
		for (int i = 0; i < listBossHand.size(); i++)
		{
			listBossHand[i]->setAlpha(alpha);
			listBossHand[i]->Render();
		}

		RenderBoundingBox();
	}
}

void CBoss::ChangeAnimation(STATEOBJECT StateObject) {
	this->StateObject = StateObject;
	AnimationSets* animation_sets = AnimationSets::GetInstance();
	LPANIMATION_SET animationSet = animation_sets->Get(type);
	CurAnimation = animationSet->Get(this->StateObject);
}

void CBoss::Reset() {
	nx = 1;
	ChangeAnimation(BOSS_MOVE);
	SetPosition(111 * BIT, 66 * BIT);
}

//boss dung yen khi bi ban trung
void CBoss::Sleep() {
	/*for (int i = 0; i < i; i++) {

	}*/
}


void CBoss::Fire() {
	if (timeStartAttack == TIME_DEFAULT) {
		timeStartAttack = GetTickCount();
		IsFiring = false;
	}
	if (GetTickCount() - timeStartAttack >= 1400 && timeStartAttack != TIME_DEFAULT) {
		bullet = new EnemyBullet();
		bullet->type = ENEMY_BULLET;
		bullet->SetPosition(x + 60 / 2, y + 66 / 3);
		bullet->ChangeAnimation(BOSS_BULLET);
		IsFiring = true;
		timeStartAttack = TIME_DEFAULT;
	}
}

void CBoss::WakeUp() {
	isWakingUp = true;
}

