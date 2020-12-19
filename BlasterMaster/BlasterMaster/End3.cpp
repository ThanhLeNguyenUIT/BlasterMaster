#include "End3.h"
#include "Brick.h"

End3::End3()
{
	type = END3;
}

void End3::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
}

void End3::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);
	x += dx;
	y += dy;
}

void End3::Render()
{
	int alpha = 255;

	CurAnimation->Render(x, y, alpha);

	//RenderBoundingBox();
}

void End3::ChangeAnimation(STATEOBJECT state) {
	this->StateObject = state;
	AnimationSets* animation_sets = AnimationSets::GetInstance();
	LPANIMATION_SET animationSet = animation_sets->Get(type);
	CurAnimation = animationSet->Get(this->StateObject);
	switch (StateObject) {
	case A:
	case C:
	case E:
	case G:
	case H:
	case I:
	case L:
	case M:
	case N:
	case O:
	case Q:
	case R:
	case T:
	case U:
	case Y:
		vx = 0;
		vy = -0.02f;
		break;
	}
}

