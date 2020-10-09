#include "Map.h"
#include "Textures.h"
#include "Car.h"

Map* Map::_instance = NULL;

Map::Map()
{
}
void Map::LoadResources(int level)
{
	ifstream File;
	char gridFileName[30];
	sprintf_s(gridFileName, "text\\Level%d.txt", level);
	File.open(gridFileName, level);
	File >> col >> row;
	mapTiles = new int* [row];
	for (int r = 0; r < row; ++r)
	{
		mapTiles[r] = new int[col];
		for (int c = 0; c < col; ++c)
		{
			File >> mapTiles[r][c];
		}
	}

	File.close();
}

void Map::Render(int level)
{
	CTextures* textures = CTextures::GetInstance();
	LPDIRECT3DTEXTURE9 texMap;
	texMap = textures->Get(60);
	CSprites* sprites = CSprites::GetInstance();
	sprites->Add(99999, 0, 0, 32, 1568, texMap);

	CSprite* sprite = sprites->Get(99999);


	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
		{
			RECT r; // bounding box of title red
			r.left = j * TITLE_WIDTH;
			r.top = i * TITLE_HEIGHT;
			r.right = r.left + TITLE_WIDTH;
			r.bottom = r.top + TITLE_HEIGHT;
			//if (IsCollision(cam->GetBound(), r)) // if title rect touch the Camera rect then do not draw 
			sprite->Draw(r.left, r.top - 60, TITLE_WIDTH * mapTiles[i][j] - TITLE_WIDTH, 0, TITLE_HEIGHT * mapTiles[i][j], TITLE_HEIGHT);
		}

}
//bool Map::IsCollision(RECT rect1, RECT rect2)
//{
//	if (rect1.left > rect2.right || rect1.right < rect2.left || rect1.top > rect2.bottom || rect1.bottom < rect2.top)
//		return false;
//	return true;
//}
void Map::Update(float dt)
{
	SetCamPos(player->x - SCREEN_WIDTH / 2, player->y - SCREEN_HEIGHT / 2);

}
Map* Map::GetInstance()
{
	if (_instance == NULL)
		_instance = new Map();
	return _instance;
}
Map::~Map()
{
}
