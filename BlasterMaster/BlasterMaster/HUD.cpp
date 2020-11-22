#include "HUD.h"
#include "Camera.h"
HUD::HUD(int playerHP)
{
	healthBar_ani_set = AnimationSets::GetInstance()->Get(HEALTHBAR);
	healthPlayer = new Health();
}

HUD::~HUD() {}

void HUD::Update(){
	healthPlayer->Update();
}

void HUD::Render()
{
	// render health bar
	float healthBarX = Camera::GetInstance()->GetCamPosX() + 1 * BIT;
	float healthBarY = Camera::GetInstance()->GetCamPosY() + 9 * BIT;
	healthBar_ani_set->Get(HEALTHBAR_NORMAL)->Render(healthBarX, healthBarY);
	// render health
	healthPlayer->Render(healthBarX, healthBarY);
}