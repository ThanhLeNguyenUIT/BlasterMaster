#include "End.h"
#include "Brick.h"

End::End()
{
	type = END;
}

void End::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
}

void End::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);
	x += dx;
	y += dy;
}

void End::Render()
{
	int alpha = 255;

	CurAnimation->Render(x, y, alpha);

	//RenderBoundingBox();
}

void End::ChangeAnimation(STATEOBJECT state) {
	this->StateObject = state;
	AnimationSets* animation_sets = AnimationSets::GetInstance();
	LPANIMATION_SET animationSet = animation_sets->Get(type);
	CurAnimation = animationSet->Get(this->StateObject);
}

