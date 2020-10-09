#include "Sprites.h"
#include "Game.h"
#include "debug.h"

CSprite::CSprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 texture) {
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->texture = texture;
}

CSprites* CSprites::__instance = NULL;

CSprites* CSprites::GetInstance() {
	if (__instance == NULL) __instance = new CSprites();
	return __instance;
}

void CSprite::Draw(float x, float y, int alpha) {
	CGame* game = CGame::GetInstance();
	game->Draw(x, y, texture, left, top, right, bottom);
}

void CSprite::Draw(float x, float y, float left, float top, float right, float bottom)
{
	CGame* game = CGame::GetInstance();
	game->Draw(x, y, texture, left, top, right, bottom, 245);
}

void CSprites::Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 texture) {
	LPSPRITE s = new CSprite(id, left, top, right, bottom, texture);
	CSprites::sprites[id] = s;
}

void CSprites::LoadResources() {
	ifstream File;
	File.open(L"text\\sprites.txt");
	int idSprites, left, top, right, bottom, idTex;
	CTextures* textures = CTextures::GetInstance();
	while (!File.eof()) {
		File >> idSprites >> left >> top >> right >> bottom >> idTex;
		LPDIRECT3DTEXTURE9 textCar = textures->Get(idTex);
		Add(idSprites, left, top, right, bottom, textCar);
	}
	File.close();
}

LPSPRITE CSprites::Get(int id) {
	return sprites[id];
}

void CAnimation::Add(int spriteId, DWORD time) {
	int t = time;
	if (time == 0) t = this->defaultTime;

	LPSPRITE sprite = CSprites::GetInstance()->Get(spriteId); // question
	LPANIMATION_FRAME frame = new CAnimationFrame(sprite, t);
	frames.push_back(frame);
}

void CAnimation::Render(float x, float y, int alpha) {

	DWORD now = GetTickCount();
	if (currentFrame == -1) {
		currentFrame = 0;
		lastFrameTime = now;
	}
	else {
		DWORD t = frames[currentFrame]->GetTime();  // question
		if (now - lastFrameTime > t) {
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size()) {
				currentFrame = 0;
				IsLastFrame = true;
			}
			else {
				IsLastFrame = false;
				t += now - lastFrameTime;
			}
		}
	}
	frames[currentFrame]->GetSprite()->Draw(x, y, alpha);
}

CAnimations* CAnimations::__instance = NULL;

CAnimations* CAnimations::GetInstance() {
	if (__instance == NULL) __instance = new CAnimations();
	return __instance;
}

void CAnimations::Add(int id, LPANIMATION ani) {
	animations[id] = ani;
}

void CAnimations::LoadResource() {
	ifstream File;
	File.open(L"text\\animations.txt");
	vector<int> ParaAni;
	ParaAni.clear();
	vector<int>::iterator it;
	int reader;
	int time;
	while (!File.eof())
	{
		File >> reader;
		if (reader > -1)
		{
			ParaAni.push_back(reader);
		}
		else
		{
			LPANIMATION ani;
			if (reader < -1)
				ani = new CAnimation(abs(reader));
			else
				ani = new CAnimation(100);
			for (auto it = ParaAni.begin(); it != ParaAni.end() - 1; ++it)
				ani->Add(*it);
			it = ParaAni.end() - 1;
			Add(*it, ani);
			ParaAni.clear();
		}
	}
	File.close();
}

LPANIMATION CAnimations::Get(int id) {
	return animations[id];
}