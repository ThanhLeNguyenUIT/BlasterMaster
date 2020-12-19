#include "HUD.h"
#include "Camera.h"

HUD* HUD::_instance = NULL;

HUD::HUD(int playerHP)
{
	healthBar_ani_set = AnimationSets::GetInstance()->Get(HEALTHBAR);
	hoverBar_ani_set = AnimationSets::GetInstance()->Get(HOVERBAR_NULL);
	healthPlayer = new Health();
}

HUD::~HUD() {}

void HUD::Update(){
	healthPlayer->Update();
}

void HUD::Render()
{
	// position health bar
	float healthBarX = Camera::GetInstance()->GetCamPosX() + 1 * BIT;
	float healthBarY = Camera::GetInstance()->GetCamPosY() + 9 * BIT;
	// position health bar
	float hoverBarX = Camera::GetInstance()->GetCamPosX() + 1 * BIT;
	float hoverBarY = Camera::GetInstance()->GetCamPosY() + 7 * BIT;
	
	//render health bar
	healthBar_ani_set->Get(HEALTHBAR_NORMAL)->Render(healthBarX, healthBarY);
	//render hover bar
	hoverBar_ani_set->Get(HOVERBARNULL_NORMAL)->Render(hoverBarX, hoverBarY);

	// render health
	healthPlayer->Render(healthBarX, healthBarY);
}

HUD* HUD::GetInstance() {
	if (_instance == NULL) {
		_instance = new HUD();
	}
	return _instance;
}