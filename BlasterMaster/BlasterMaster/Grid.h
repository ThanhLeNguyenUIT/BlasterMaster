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
	~Grid() {};
	int rows, cols;
	int alphaa;
	int SizeCell;
	vector<vector<Cell*>> Cells;
	vector<LPGAMEOBJECT> CurObjectInViewPort;
	vector<LPGAMEOBJECT> ObjectHolder;
	Area FindCell(RECT e);
	void Init();
	void SetSizeCell(int s) { this->SizeCell = s; }
	void LoadObjects(LPGAMEOBJECT& obj, float x, float y);
	void AddStaticObject(LPGAMEOBJECT obj, float x, float y);
	void UpdateCell();
	void UpdateStaticObject();
	void RenderCell();
	bool IsOnCam(LPGAMEOBJECT obj);
	void RemoveDeadObject();
	void AddMovingObject(LPGAMEOBJECT obj);
	void CalcObjectInViewPort();
	vector<LPGAMEOBJECT> GetObjectInViewPort() { return CurObjectInViewPort; }

};

