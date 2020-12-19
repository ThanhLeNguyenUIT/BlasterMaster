#include "Intro.h"
#include "Brick.h"

CIntro* CIntro::_instance = NULL;

CIntro::CIntro()
{
	type = INTRO;
	ChangeAnimation(INTRO_PLAY);
}

CIntro::~CIntro() {

}

void CIntro::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
}

void CIntro::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);
	if (CurAnimation->isLastFrame) {
		Game::GetInstance()->SwitchScene(1);
	}

}

void CIntro::Render()
{
	int alpha = 255;

	CurAnimation->Render(x, y, alpha);

	//RenderBoundingBox();
}

void CIntro::ChangeAnimation(STATEOBJECT StateObject) {
	this->StateObject = StateObject;
	AnimationSets* animation_sets = AnimationSets::GetInstance();
	LPANIMATION_SET animationSet = animation_sets->Get(type);
	CurAnimation = animationSet->Get(this->StateObject);
}

CIntro* CIntro::GetInstance() {
	if (_instance == NULL) {
		_instance = new CIntro();
	}
	return _instance;
}