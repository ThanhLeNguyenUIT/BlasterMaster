#include "Gate.h"


Gate::Gate(float l, float t, float r, float b, int scene_id)
{
	this->scene_id = scene_id;
	x = l;
	y = t;
	width = r;
	height = b;
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