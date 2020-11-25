#include "Map.h"
#include "Textures.h"
#include "Sophia.h"

Map* Map::_instance = NULL;

Map::Map()
{
}
void Map::LoadResources(int level)
{

}

void Map::Render()
{
	Textures* textures = Textures::GetInstance();
	LPDIRECT3DTEXTURE9 texMap;
	//if(Allow[])
	texMap = textures->Get(ID_TEX_MAP);
	Sprites* sprites = Sprites::GetInstance();
	sprites->Add(99999, 0, 0, 2048, 2048, texMap);

	Sprite* sprite = sprites->Get(99999);

	RECT r; // bounding box of title red
	r.left = 0;
	r.top =  0;
	r.right = 0;
	r.bottom = 0;
	//if (IsCollision(cam->GetBound(), r)) // if title rect touch the Camera rect then do not draw 
	sprite->Draw(r.left, r.top);


}
//bool Map::IsCollision(RECT rect1, RECT rect2)
//{
//	if (rect1.left > rect2.right || rect1.right < rect2.left || rect1.top > rect2.bottom || rect1.bottom < rect2.top)
//		return false;
//	return true;
//}
void Map::Update(float dt)
{
	//SetCamPos(player->x - SCREEN_WIDTH / 2, player->y - SCREEN_HEIGHT / 2);

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
