#include "Intro.h"
#include "Brick.h"

CIntro::CIntro(float x, float y)
{
	this->x = x;
	this->y = y;
	typeScene = INTRO;
	Reset();
}

void CIntro::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
}

void CIntro::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);

}


void CIntro::Render()
{
	int alpha = 255;
	CurAnimation->Render(x, y, alpha);
	//RenderBoundingBox();
}

void CIntro::ChangeAnimation(STATEOBJECT StateObject) {
	
}

void CIntro::Reset() {

	ChangeAnimation(Intro_STATE_IDLE);
}
