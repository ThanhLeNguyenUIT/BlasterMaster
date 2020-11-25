#pragma once
#include "Animations.h"
#include <vector>

#define ID_TEX_HEALTH_BAR	70
#define ID_TEX_HEALTH	80

class Health {
private:
	float x, y;
	int curHealth, maxHealth;	
	LPANIMATION health_ani;
public:
	Health(int health = 8);
	~Health();
	void Render(float healthBarX, float healthBarY);
	void Update();
};