#include "Brick.h"

Brick::Brick(int boxWidth, int boxHeight) {
	this->boxWidth = boxWidth; 
	this->boxHeight = boxHeight;
}

void Brick::Render() {
	//animation_set->Get(BRICK_NORMAL)->Render(x, y);
	RenderBoundingBox();
}

void Brick::GetBoundingBox(float &l, float &t, float &r, float &b) {
	l = x;
	t = y;
	r = x + boxWidth;
	b = y + boxHeight;
}

