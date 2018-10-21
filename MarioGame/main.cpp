#include<Windows.h>
#include<dos.h>
#include "Graphics.h"
#include "GameLevel.h"
#include "GameController.h"
#include "Level1.h"

Graphics* graphics;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_DESTROY)
	{
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmd, int nCmdShow)
{
	WNDCLASSEX windowclass;
	ZeroMemory(&windowclass, sizeof(WNDCLASSEX));
	windowclass.cbSize = sizeof(WNDCLASSEX);
	windowclass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowclass.hInstance = hInstance;
	windowclass.lpfnWndProc = WindowProc;
	windowclass.lpszClassName = "MainWindow";
	windowclass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&windowclass);

	HWND hwnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "MainWindow", "Mario Game", WS_OVERLAPPEDWINDOW,CW_USEDEFAULT , CW_USEDEFAULT,300, 200, NULL, NULL, hInstance, 0);

	if (!hwnd) return -1;

	graphics = new Graphics();
	if (!graphics->Init(hwnd))
	{
		delete graphics;
		return -1;
	}

	GameLevel::Init(graphics);

	ShowWindow(hwnd, SW_MAXIMIZE);

	GameController::Init();
	GameController::LoadInitialLevel(new Level1);

	MSG message;
	message.message = WM_NULL;
	while (message.message != WM_QUIT)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
			DispatchMessage(&message);
		else 
		{
			GameController::Update();

			graphics->BeginDraw();
			GameController::Render();
			graphics->EndDraw();

		}
	}

	return 0;
}