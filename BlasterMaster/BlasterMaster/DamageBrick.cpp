#include "DamageBrick.h"

DamageBrick::DamageBrick(int boxWidth, int boxHeight) {
	this->boxWidth = boxWidth;
	this->boxHeight = boxHeight;
}

void DamageBrick::Render() {
	//RenderBoundingBox();
}

void DamageBrick::GetBoundingBox(float& l, float& t, float& r, float& b) {
	l = x;
	t = y;
	r = x + boxWidth;
	b = y + boxHeight;
}

