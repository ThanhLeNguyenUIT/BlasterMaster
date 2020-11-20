#include "HUD.h"
#include "Camera.h"
HUD::HUD(int playerHP)
{
	healthBar_ani_set = AnimationSets::GetInstance()->Get(HEALTHBAR);
	if(Allow[SOPHIA])
		sophiaHP = new Health(player->health);
}

HUD::~HUD() {}

void HUD::Update(){
	sophiaHP->Update();
}

void HUD::Render()
{
	// render health bar
	float healthBarX = Camera::GetInstance()->GetCamPosX() + 1 * BIT;
	float healthBarY = Camera::GetInstance()->GetCamPosY() + 9 * BIT;
	healthBar_ani_set->Get(HEALTHBAR_NORMAL)->Render(healthBarX, healthBarY);
	// render health
	sophiaHP->Render(healthBarX, healthBarY);
}