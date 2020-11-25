#include "Stair.h"

Stair::Stair(int boxWidth, int boxHeight) {
	this->boxWidth = boxWidth;
	this->boxHeight = boxHeight;
}

void Stair::Render() {
	//animation_set->Get(BRICK_NORMAL)->Render(x, y);
	RenderBoundingBox();
}

void Stair::GetBoundingBox(float& l, float& t, float& r, float& b) {
	l = x;
	t = y;
	r = x + boxWidth;
	b = y + boxHeight;
}
