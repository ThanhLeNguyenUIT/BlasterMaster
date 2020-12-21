#include "Thunder.h"

Thunder::Thunder() {
	ChangeAnimation(THUNDER_UP);
	width = ITEM_BBOX_WIDTH;
	height = ITEM_BBOX_HEIGHT;
}

Thunder::~Thunder() {

}

void Thunder::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

}


void Thunder::ChangeAnimation(STATEOBJECT StateObject) {
	this->StateObject = StateObject;
	AnimationSets* animation_sets = AnimationSets::GetInstance();
	LPANIMATION_SET animationSet = animation_sets->Get(type);
	CurAnimation = animationSet->Get(this->StateObject);
}

void Thunder::Render() {
	int alpha = 255;
	CurAnimation->Render(x, y, alpha);
	RenderBoundingBox();
}

void Thunder::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + ITEM_BBOX_WIDTH;
	bottom = y + ITEM_BBOX_HEIGHT;
}