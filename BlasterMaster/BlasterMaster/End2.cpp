#include "End2.h"
#include "Brick.h"

End2::End2()
{
	type = END2;
}

void End2::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
}

void End2::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);
	x += dx;
	y += dy;
}

void End2::Render()
{
	int alpha = 255;

	CurAnimation->Render(x, y, alpha);

	//RenderBoundingBox();
}

void End2::ChangeAnimation(STATEOBJECT state) {
	this->StateObject = state;
	AnimationSets* animation_sets = AnimationSets::GetInstance();
	LPANIMATION_SET animationSet = animation_sets->Get(type);
	CurAnimation = animationSet->Get(this->StateObject);
}

