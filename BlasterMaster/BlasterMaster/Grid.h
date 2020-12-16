#pragma once
#include "Cell.h"
#define LOOP(x, y, z) for (int x = y; x <= z; x++)
struct  Area
{
	int  TopCell, LeftCell, RightCell, BottomCell;
};
class Grid
{
private:
	static Grid* __instance;
public:

	static Grid* GetInstance();
	Grid();
	~Grid();
	int rows, cols;
	int alpha;
	int SizeCell = 90;
	vector<vector<Cell*>> Cells;
	vector<LPGAMEOBJECT> CurStaticObjectInViewPort;
	vector<LPGAMEOBJECT> CurMovingObjectInViewPort;
	vector<LPGAMEOBJECT> ObjectHolder;
	void Init();
	void RenderCell();
	void UpdateCell();
	Area FindCell(RECT e);
	void SetCellSize(int SizeCell) { this->SizeCell = SizeCell; }
	
	void LoadObject(LPGAMEOBJECT& obj, float x, float y, float width = 0, float height = 0, int scene_id = 0);

	void AddStaticObject(LPGAMEOBJECT obj, float x, float y);
	void AddMovingObject(LPGAMEOBJECT obj);
	void RemoveDeadObject();

	void CalcObjectInViewPort();
	vector<LPGAMEOBJECT> GetStaticObjectInViewPort() { return CurStaticObjectInViewPort; }
	vector<LPGAMEOBJECT> GetMovingObjectInViewPort() { return CurMovingObjectInViewPort; }
};

