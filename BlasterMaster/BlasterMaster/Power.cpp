#include "Power.h"

Power::Power() {
	ChangeAnimation(POWER_UP);
	width = ITEM_BBOX_WIDTH;
	height = ITEM_BBOX_HEIGHT;
}

Power::~Power() {

}

void Power::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

}


void Power::ChangeAnimation(STATEOBJECT StateObject) {
	this->StateObject = StateObject;
	AnimationSets* animation_sets = AnimationSets::GetInstance();
	LPANIMATION_SET animationSet = animation_sets->Get(type);
	CurAnimation = animationSet->Get(this->StateObject);
}

void Power::Render() {
	int alpha = 255;
	CurAnimation->Render(x, y, alpha);
	RenderBoundingBox();
}

void Power::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + ITEM_BBOX_WIDTH;
	bottom = y + ITEM_BBOX_HEIGHT;
}