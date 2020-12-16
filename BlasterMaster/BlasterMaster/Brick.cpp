#include "Brick.h"

Brick::Brick() {
	type = BRICK;
}

void Brick::Render() {
	RenderBoundingBox();
}

void Brick::GetBoundingBox(float &l, float &t, float &r, float &b) {
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}

