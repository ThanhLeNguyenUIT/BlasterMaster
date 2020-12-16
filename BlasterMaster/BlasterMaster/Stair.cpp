#include "Stair.h"

Stair::Stair() {
	type = STAIR;
}

void Stair::Render() {
	RenderBoundingBox();
}

void Stair::GetBoundingBox(float& l, float& t, float& r, float& b) {
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}
