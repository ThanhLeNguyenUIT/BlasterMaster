#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>
#include "Game.h"
#include <fstream>
#include "Textures.h"
using namespace std;

class CSprite {
	int id; // Sprite id in the database

	int left;
	int right;
	int bottom;
	int top;

	LPDIRECT3DTEXTURE9 texture;

public:
	CSprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 texture);

	void Draw(float x, float y, int alpha = 255);
	void Draw(float x, float y, float left, float top, float right, float bottom);
};

typedef CSprite* LPSPRITE;

class CSprites {
	static CSprites* __instance;

	unordered_map<int, LPSPRITE> sprites;

public:
	void Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);
	LPSPRITE Get(int id);

	void LoadResources();

	static CSprites* GetInstance();
};
