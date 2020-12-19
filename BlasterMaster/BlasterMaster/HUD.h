#pragma once
#include "GameObject.h"
#include "Health.h"
#include "Sophia.h"
#include "Jason.h"
#include "BigJason.h"


using namespace std;


class HUD
{
	Health* healthPlayer;
	LPANIMATION_SET healthBar_ani_set;
	LPANIMATION_SET hoverBar_ani_set;
public:
	HUD(int playerHP = 8);
	~HUD();
	void Update();
	void Render();
	static HUD* _instance;
	static HUD* GetInstance();
};
