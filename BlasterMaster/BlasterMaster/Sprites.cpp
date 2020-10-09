#include "Sprites.h"
#include "Textures.h"

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


