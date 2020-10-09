#pragma once
#include <unordered_map>
#include "debug.h"
#include "GlobalConfig.h"
#include "Game.h"
#include <fstream>

using namespace std;

class CTextures {
	static CTextures* __instance;
	unordered_map <int, LPDIRECT3DTEXTURE9> textures;
public:
	CTextures();
	void Add(int id, LPCWSTR filePath, D3DCOLOR transparentColor);
	LPDIRECT3DTEXTURE9 Get(unsigned int i);

	void LoadResources();

	static CTextures* GetInstance();
};