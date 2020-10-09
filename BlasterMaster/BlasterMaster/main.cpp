

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"
#include "Map.h"

#include "Car.h"
#include "Brick.h"
#include "Goomba.h"
#include "Bullet.h"

#include "PlayerStandingState.h"

#define WINDOW_CLASS_NAME L"Game"
#define MAIN_WINDOW_TITLE L"Game"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(173, 216, 230)


#define MAX_FRAME_RATE 90

#define ID_TEX_CAR 0
#define ID_TEX_ENEMY 40
#define ID_TEX_MISC 50
#define ID_TEX_BULLET 30



//using namespace std;

CGame* game;
CCar* car;
CGoomba* goomba;
CBullet* bullet;
Map* map = Map::GetInstance();
//CGameObject* brick;

vector<LPGAMEOBJECT> objects;

class CSampleKeyHandler : public CKeyEventHandler {
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

CSampleKeyHandler* keyHandler;

void CSampleKeyHandler::OnKeyDown(int KeyCode) {
	
	keyCode[KeyCode] = true;
	player->OnKeyDown(KeyCode);
	
	switch (KeyCode) {
	case DIK_A:
		car = new CCar();
		car = player;
		car->Revival();
	}
}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	keyCode[KeyCode] = false;
	player->OnKeyUp(KeyCode);
}

void CSampleKeyHandler::KeyState(BYTE *states) {

}



LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}



void LoadResources(){
	CTextures* textures = CTextures::GetInstance();
	textures->LoadResources();

	CSprites* sprites = CSprites::GetInstance();
	sprites->LoadResources();
	
	CAnimations* animations = CAnimations::GetInstance();
	animations->LoadResource();

	//Map::GetInstance()->LoadResources(1);

	//// sprite car moving right
	////sprites->Add(10001, 146, 5, 172, 23, textCar); // state idle
	//sprites->Add(10001, 146, 31, 172, 48, textCar);
	//sprites->Add(10002, 146, 56, 172, 72, textCar);
	////sprites->Add(10004, 178, 5, 204, 23, textCar);
	//sprites->Add(10003, 178, 31, 204, 48, textCar);
	//sprites->Add(10004, 177, 56, 203, 72, textCar);
	//sprites->Add(10005, 211, 5, 237, 23, textCar);
	//sprites->Add(10006, 242, 5, 268, 23, textCar);


	// //sprite car moving left
	//sprites->Add(10011, 109, 5, 135, 23, textCar);
	//sprites->Add(10012, 77, 5, 103, 23, textCar);
	//sprites->Add(10013, 44, 5, 70, 23, textCar);
	//sprites->Add(10014, 13, 5, 39, 23, textCar);

	////sprite car upward right
	//sprites->Add(10020, 146, 187, 171, 213, textCar);
	//sprites->Add(10021, 146, 218, 171, 246, textCar);
	//sprites->Add(10022, 146, 250, 171, 280, textCar);
	//sprites->Add(10023, 146, 283, 172, 317, textCar);

	////sprite car upward left
	//sprites->Add(10024, 110, 187, 135, 213, textCar);
	//sprites->Add(10025, 110, 218, 135, 246, textCar);
	//sprites->Add(10026, 110, 250, 135, 280, textCar);
	//sprites->Add(10027, 109, 283, 135, 317, textCar);


	////sprite car jump

	////sprite car gun up

	// //sprite brick
	//LPDIRECT3DTEXTURE9 texMisc = textures->Get(ID_TEX_MISC);
	//sprites->Add(20001, 408, 225, 424, 241, texMisc);

	////sprite goomba
	//LPDIRECT3DTEXTURE9 texEnemy = textures->Get(ID_TEX_ENEMY);
	//sprites->Add(30001, 5, 14, 21, 29, texEnemy);
	//sprites->Add(30002, 25, 14, 41, 29, texEnemy);

	//sprites->Add(30003, 45, 21, 61, 29, texEnemy); // die sprite

	////sprite bullet
	//LPDIRECT3DTEXTURE9 textBullet = textures->Get(ID_TEX_BULLET);
	//sprites->Add(40000, 300, 113, 326, 121, textBullet);
	//sprites->Add(40001, 304, 158, 322, 176, textBullet); // bullet explose
	
	/*LPANIMATION ani;*/

	//ani = new CAnimation(100); // standing right
	//ani->Add(10001);
	//animations->Add(400, ani);

	//ani = new CAnimation(100); // standing left
	//ani->Add(10011);
	//animations->Add(401, ani);

	//ani = new CAnimation(100); // animtation moving right
	//ani->Add(10001);
	//ani->Add(10002);
	//ani->Add(10003);
	//ani->Add(10004);
	//ani->Add(10005);
	//ani->Add(10006);
	////ani->Add(10007);
	////ani->Add(10008);
	//animations->Add(500, ani);

	//ani = new CAnimation(100); // animation moving left
	//ani->Add(10011);
	//ani->Add(10012);
	//ani->Add(10013);
	//ani->Add(10014);
	//animations->Add(501, ani);	

	//ani = new CAnimation(100); // Upward right
	//ani->Add(10020);
	//ani->Add(10021);
	//ani->Add(10022);
	//ani->Add(10023);
	//animations->Add(510, ani);

	//ani = new CAnimation(100); // Upward left
	//ani->Add(10024);
	//ani->Add(10025);
	//ani->Add(10026);
	//ani->Add(10027);
	//animations->Add(511, ani);

	//ani = new CAnimation(100); // Up right
	//ani->Add(10023);
	//animations->Add(512, ani);
	//ani = new CAnimation(100); // Up left
	//ani->Add(10027);
	//animations->Add(513, ani);

	//ani = new CAnimation(100);		// brick
	//ani->Add(20001);
	//animations->Add(600, ani);

	//ani = new CAnimation(300);		// Goomba walk
	//ani->Add(30001);
	//ani->Add(30002);
	//animations->Add(700, ani);

	//ani = new CAnimation(1000);		// Goomba dead
	//ani->Add(30003);
	//animations->Add(701, ani);

	//ani = new CAnimation(100);   // bullet
	//ani->Add(40000);
	//animations->Add(800, ani);

	//ani = new CAnimation(100);  // bullet explose
	//ani->Add(40001);
	//animations->Add(801, ani);


	car = player;
	car->Revival();
	objects.push_back(car);

	CBrick* brick = new CBrick();
	brick->AdAnimation(600);
	brick->SetPosition(100.0, 134.0f);
	objects.push_back(brick);

	brick = new CBrick();
	brick->AdAnimation(600);
	brick->SetPosition(100.0f, 118.0f);
	objects.push_back(brick);

	for (int i = 0; i < 50; i++)
	{
		CBrick* brick = new CBrick();
		brick->AdAnimation(600);
		brick->SetPosition(0 + i * 16.0f, 245);
		objects.push_back(brick);
	}

	/*for (int i = 0; i < 4; i++)
	{
		goomba = new CGoomba();
		goomba->AdAnimation(700);
		goomba->AdAnimation(701);
		goomba->SetPosition(200 + i * 60, 135);
		goomba->SetState(GOOMBA_STATE_WALKING);
		objects.push_back(goomba);
	}*/

	
}
void Update(DWORD dt){
	vector<LPGAMEOBJECT> coObjects;

	float cx, cy;
	float bx, by;
	bool isFiring = false;
	car->GetPosition(cx, cy);

	for (int i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}
	//for (int i = 0; i < objects.size(); i++) {
	//	if (objects[i]->GetState() == GOOMBA_STATE_DIE) {
	//		objects.erase(objects.begin() + i);
	//	}
	//}
	cx -= SCREEN_WIDTH / 2;
	cy -= SCREEN_HEIGHT / 2;

	CGame::GetInstance()->SetCamPos(cx, 0.0f /*cy*/);
}

/*
Render a frame
*/
void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene()) {
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);
		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		//Map::GetInstance()->Render(1);
		for (int i = 0; i < objects.size(); i++)
			objects[i]->Render();
		 
		spriteHandler->End();
		d3ddv->EndScene();
	}
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd)
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;
		if (dt >= tickPerFrame)
		{
			frameStart = now;

			game->ProcessKeyboard();
			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);
	}

	return 1;
}   

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);
	
	game = CGame::GetInstance();
	game->Init(hWnd);

	keyHandler = new CSampleKeyHandler();
	game->InitKeyboard(keyHandler);
	
	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	LoadResources();
	Run();

	return 0;
}


