#include "Grid.h"
#include "Sophia.h"
#include "Camera.h"

Grid* Grid::__instance = NULL;
Grid::Grid() {}
Grid::~Grid() {}

Grid* Grid::GetInstance()
{
	if (__instance == NULL)
		__instance = new Grid();
	return __instance;
}


Area Grid::FindCell(RECT e) {
	return {
		int(max(0		, e.top / SizeCell)),
		int(max(0		, e.left / SizeCell)),
		int(min(cols - 1, int(e.right / SizeCell))),
		int(min(rows - 1, int(e.bottom / SizeCell)))
	};
}

void Grid::Init() {

	Cells.clear();
	for (int y = 0; y < rows; ++y)
	{
		auto row = std::vector<Cell*>();
		for (int x = 0; x < cols; ++x)
		{
			row.push_back(new Cell(x, y));
		}
		Cells.push_back(row);
	}
}

void Grid::LoadObject(LPGAMEOBJECT& obj, float x, float y, float width, float height, int scene_id) {
	RECT e;
	e.top = y;
	e.left = x;
	e.right = x + obj->GetRect().right;
	e.bottom = y + obj->GetRect().bottom;
	
	auto area = FindCell(e);
	switch (obj->type){
	case BRICK:
	case DAMAGE_BRICK:
	case STAIR:
	case GATE:
	case PORTAL:
		for (int r = area.TopCell; r <= area.BottomCell; r++)
			for (int c = area.LeftCell; c <= area.RightCell; c++)
			{
				Cells[r][c]->staticObjects.insert(obj);
			}
		obj->SetPosition(x, y);
		break;
	case WORM:
	case FLOATER:
	case JUMPER:
	case INSECT:
	case DOME:
	case ORB1:
	case ORB2:
	case SKULL:
	case MINE:
	case CANON:
	case EYEBALL:
	case TELEPORTER:
		for (int r = area.TopCell; r <= area.BottomCell; r++)
			for (int c = area.LeftCell; c <= area.RightCell; c++)
			{
				Cells[r][c]->movingObjects.insert(obj);
			}
		obj->SetPosition(x, y);
		break;
	default:
		DebugOut(L"[ERR] Invalid object TYPE: %d\n", obj->type);
		break;
	}
}

void Grid::RenderCell() {

	LPDIRECT3DTEXTURE9 bbox = Textures::GetInstance()->Get(ID_TEX_BBOX);
	auto area = FindCell(camera->GetBound());

	RECT rect;

	for (int r = area.TopCell; r <= area.BottomCell; r++)
	{
		for (int c = area.LeftCell; c <= area.RightCell; c++)
		{
			LPD3DXSPRITE spriteHandler = Game::GetInstance()->GetSpriteHandler();
			
			SetRect(&rect,
				Cells[r][c]->posX * SizeCell,
				Cells[r][c]->posY * SizeCell,
				Cells[r][c]->posX * SizeCell + SizeCell,
				Cells[r][c]->posY * SizeCell + SizeCell);
			Game::GetInstance()->Draw(rect.left, rect.top, bbox, rect.left, rect.top, rect.left + SizeCell, rect.top + 1, 150);
			Game::GetInstance()->Draw(rect.left, rect.top, bbox, rect.left, rect.top, rect.left + 1, rect.top + SizeCell, 150);

		}
	}
}

template<typename T, typename Pred>
void RemoveObjectIf(unordered_set<T>& container, Pred  del)
{
	for (auto it = container.begin(), end = container.end(); it != end; )
	{
		if (del(*it)) it = container.erase(it);
		else                       it++;
	}
}

void Grid::UpdateCell() {
	auto area = FindCell(camera->GetBound());
	unordered_set<LPGAMEOBJECT> shouldBeUpdatedObjects;
	bool isDeadObject = false;
	LOOP(r, area.TopCell, area.BottomCell)
		LOOP(c, area.LeftCell, area.RightCell)
	{
		if (Cells[r][c]->movingObjects.size() == 0) continue;
		RemoveObjectIf(Cells[r][c]->movingObjects, [&](auto& obj)
			{
				RECT e;
				e.left = obj->x;
				e.top = obj->y;
				e.right = obj->x + obj->width;
				e.bottom = obj->y + obj->height;
				auto objArea = FindCell(e);
				if (obj->isDead) isDeadObject = true;
				if (objArea.TopCell != r || objArea.RightCell != c)
				{
					shouldBeUpdatedObjects.emplace(obj);
					return true;
				}
				return false;
			});
	}
	LOOP(r, area.TopCell, area.BottomCell)
		LOOP(c, area.LeftCell, area.RightCell)
	{
		if (Cells[r][c]->staticObjects.size() == 0) continue;
		RemoveObjectIf(Cells[r][c]->staticObjects, [&](auto& obj)
			{
				RECT e;
				e.left = obj->x;
				e.top = obj->y;
				e.right = obj->x + obj->width;
				e.bottom = obj->y + obj->height;
				auto objArea = FindCell(e);
				if (obj->isDead)
				{
					return true;
					isDeadObject = true;
				}
				return false;
			});
	}
	for (auto& obj : shouldBeUpdatedObjects)
	{
		RECT e;
		e.left = obj->x;
		e.top = obj->y;
		e.right = obj->x + obj->width;
		e.bottom = obj->y + obj->height;
		auto objArea = FindCell(e);
		LOOP(r, objArea.TopCell, objArea.BottomCell)
			LOOP(c, objArea.LeftCell, objArea.RightCell)
		{
			Cells[r][c]->movingObjects.emplace(obj);
		}
	}
	if (isDeadObject) RemoveDeadObject();
	CalcObjectInViewPort();
}

void Grid::AddStaticObject(LPGAMEOBJECT obj, float x, float y) {
	RECT e;
	e.left = x;
	e.top = y;
	e.right = x + obj->width;
	e.bottom = y + obj->height;
	auto area = FindCell(e);
	LOOP(r, area.TopCell, area.BottomCell)
		LOOP(c, area.LeftCell, area.RightCell)
		Cells[r][c]->staticObjects.insert(obj);
	obj->SetPosition(x, y);
}

void Grid::AddMovingObject(LPGAMEOBJECT obj) {
	RECT e;
	e.left = obj->x;
	e.top = obj->y;
	e.right = obj->x + obj->width;
	e.bottom = obj->y + obj->height;

	auto area = FindCell(e);
	LOOP(r, area.TopCell, area.BottomCell)
		LOOP(c, area.LeftCell, area.RightCell)
		Cells[r][c]->movingObjects.insert(obj);
}

void Grid::RemoveDeadObject() {
	auto area = FindCell(camera->GetBound());
	LOOP(r, area.TopCell, area.BottomCell)
		LOOP(c, area.LeftCell, area.RightCell)
	{
		RemoveObjectIf(Cells[r][c]->movingObjects, [](auto obj) {return obj->isDead; });
	}
}

void Grid::CalcObjectInViewPort() {
	auto area = FindCell(camera->GetBound());

	unordered_set<GameObject*> resultStaticObject;
	unordered_set<GameObject*> resultMovingObject;

	for (int r = area.TopCell; r <= area.BottomCell; r++) {
		for (int c = area.LeftCell; c <= area.RightCell; c++) {
			resultStaticObject.insert(Cells[r][c]->staticObjects.begin(), Cells[r][c]->staticObjects.end());
			resultMovingObject.insert(Cells[r][c]->movingObjects.begin(), Cells[r][c]->movingObjects.end());
		}
	}
	CurStaticObjectInViewPort = { resultStaticObject.begin(), resultStaticObject.end() };
	CurMovingObjectInViewPort = { resultMovingObject.begin(), resultMovingObject.end() };
}