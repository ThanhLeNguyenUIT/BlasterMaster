#include "Gate.h"


Gate::Gate(){
	type = GATE;
}

void Gate::Render()
{
	RenderBoundingBox();
}

void Gate::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}