#pragma
#include "Health.h"
#include "Camera.h"
#include "Sophia.h"
#include "Jason.h"
#include "BigJason.h"

Health::Health(int health) {
	curHealth = health;
	LPANIMATION_SET health_ani_set = AnimationSets::GetInstance()->Get(HEALTH);
	health_ani = health_ani_set->Get(HEALTH_NORMAL);
}

Health::~Health() {
}

void Health::Render(float healthBarX, float healthBarY) {
	if (curHealth <= 0)
		return;
	else {
		for (int i = 0; i < curHealth; i++)
		{
			health_ani->Render(healthBarX + 1, healthBarY + 29 - i * 4);
		}
	}
}

void Health::Update() {
	if (Allow[SOPHIA]) {
		curHealth = player->health;
	}
	else if (Allow[JASON]) {
		curHealth = playerSmall->health;
	}
	else if (Allow[BIG_JASON]) {
		curHealth = playerBig->health;
	}
}

