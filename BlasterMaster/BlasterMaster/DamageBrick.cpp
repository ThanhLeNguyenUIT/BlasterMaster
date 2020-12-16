#include "DamageBrick.h"

DamageBrick::DamageBrick() {
	type = DAMAGE_BRICK;
}

void DamageBrick::Render() {
	RenderBoundingBox();
}

void DamageBrick::GetBoundingBox(float& l, float& t, float& r, float& b) {
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}

