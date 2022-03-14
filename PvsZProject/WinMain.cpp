#include "Stdafx.h"
#include "MainGame.h"

HINSTANCE _hInstance;
HWND _hWnd;
POINT _ptMouse = { 0, 0 };

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height);

MainGame* _mg;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) {
	_mg = new MainGame();
	_hInstance = hInstance;

	WNDCLASS wndclass;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = WINNAME;
	wndclass.lpszMenuName = NULL;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wndclass);

#ifdef FULLSCREEN
	DEVMODE dm;
	ZeroMemory(&dm, sizeof(DEVMODE));
	
	dm.dmBitsPerPel = 32;
	dm.dmPelsWidth = 1920;
	dm.dmPelsHeight = 1080;
	dm.dmDisplayFrequency = 60;

	dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;
	if (ChangeDisplaySettings(&dm, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL) {
		ChangeDisplaySettings(&dm, 0);
	}
	_hWnd = CreateWindow(WINNAME, WINNAME, WINSTYLE, WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y, NULL, (HMENU)NULL, hInstance, NULL);
	setWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);

#else
	_hWnd = CreateWindow(WINNAME, WINNAME, WINSTYLE, WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y, NULL, (HMENU)NULL, hInstance, NULL);
	setWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);
#endif

	ShowWindow(_hWnd, nCmdShow);

	if (FAILED(_mg->init())) return 0;

	MSG message;
	while (true) {
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
			if (message.message == WM_QUIT) break;
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else {
			TIMEMANAGER->update(60.0);
			_mg->update();
			_mg->render();
		}
	}

	//while (GetMessage(&message, 0, 0, 0)) {
	//	TranslateMessage(&message);
	//	DispatchMessage(&message);
	//}

	_mg->release();
	UnregisterClass(WINNAME, hInstance);
	return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT imessage, WPARAM wparam, LPARAM lparam) {
	return _mg->MainProc(hwnd, imessage, wparam, lparam);
}

void setWindowSize(int x, int y, int width, int height) {
	RECT rc = { 0, 0, width, height };
	AdjustWindowRect(&rc, WINSTYLE, false);
	SetWindowPos(_hWnd, NULL, x, y, (rc.right - rc.left), (rc.bottom - rc.top), SWP_NOZORDER | SWP_NOMOVE);
}
