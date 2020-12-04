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

void Grid::LoadObject(LPGAMEOBJECT& obj, float x, float y) {
	RECT e;
	e.top = y;
	e.left = x;
	e.right = x + obj->GetRect().right;
	e.bottom = y + obj->GetRect().bottom;
	auto area = FindCell(e);
	switch (obj->type){
	case BRICK:
	case DAMAGE_BRICK:

		break;
	}
}

void Grid::RenderCell() {
	LPDIRECT3DTEXTURE9 bbox = Textures::GetInstance()->Get(ID_TEX_BBOX);

	auto area = FindCell(camera->GetBound());
	for (int r = area.TopCell; r < area.BottomCell; r++) {
		for (int c = area.LeftCell; c < area.RightCell; c++) {
			RECT rect;
			rect.left = Cells[r][c]->posX *	SizeCell;
			rect.top = Cells[r][c]->posY * SizeCell;
			rect.right = rect.left + SizeCell;
			rect.bottom = rect.top + SizeCell;
			alpha = alpha == 20 ? 40 : 20;
			Game::GetInstance()->Draw(rect.left, rect.top, bbox, rect.left, rect.top, rect.right, rect.bottom, alpha);
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
	unordered_set<LPGAMEOBJECT> UpdateObjects;
	bool isDeadObject = false;
	LOOP(r, area.TopCell, area.BottomCell)
		LOOP(c, area.LeftCell, area.RightCell) {
		if (Cells[r][c]->movingObjects.size() == 0) continue;
		RemoveObjectIf(Cells[r][c]->staticObjects, [&](auto& obj) {
			RECT e;
			e.left = obj->x;
			e.top = obj->y;
			e.right = obj->x + obj->widthBBox;
			e.bottom = obj->y + obj->heightBBox;
			
			auto objArea = FindCell(e);
			if (obj->isDead) {
				return true;
				isDeadObject = true;
			}
			return false;
			});
	}

	for (auto& obj : UpdateObjects)
	{
		RECT e;
		e.left = obj->x;
		e.top = obj->y;
		e.right = obj->x + obj->widthBBox;
		e.bottom = obj->y + obj->heightBBox;
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
	e.right = x + obj->widthBBox;
	e.bottom = y + obj->heightBBox;
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
	e.right = obj->x + obj->widthBBox;
	e.bottom = obj->y + obj->heightBBox;

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

	unordered_set<GameObject*> result;
	unordered_set<GameObject*> resultItem;

	for (int r = area.TopCell; r <= area.BottomCell; r++) {
		for (int c = area.LeftCell; c <= area.RightCell; c++) {
			result.insert(Cells[r][c]->staticObjects.begin(), Cells[r][c]->staticObjects.end());
			result.insert(Cells[r][c]->movingObjects.begin(), Cells[r][c]->movingObjects.end());
			resultItem.insert(Cells[r][c]->staticObjects.begin(), Cells[r][c]->staticObjects.end());
		}
	}
	ObjectHolder = { resultItem.begin(), resultItem.end() };
	CurObjectInViewPort = { result.begin(), result.end() };
}