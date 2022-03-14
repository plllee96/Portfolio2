#include "Stdafx.h"
#include "TileSetting.h"

HRESULT TileSetting::init(void) {
	_input = WIDTH;
	_tileX = 2;
	_tileY = 2;
	return S_OK;
}

void TileSetting::release(void) {
}

void TileSetting::update(void) {
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN)) _input = HEIGHT;
	if (KEYMANAGER->isOnceKeyDown(VK_UP)) _input = WIDTH;
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT)) {
		if (_input == WIDTH && _tileX < 10) _tileX++;
		else if (_input == HEIGHT && _tileY < 10) _tileY++;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT)) {
		if (_input == WIDTH && _tileX > 2) _tileX--;
		else if (_input == HEIGHT && _tileY > 2) _tileY--;
	}
}

void TileSetting::render(void) {
	HFONT font;
	HFONT oldFont;

	char str[128];
	char widthStr[128];
	char heightStr[128];
	font = CreateFont(25, 0, 0, 0, 60, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("휴먼굴림"));
	oldFont = (HFONT)SelectObject(getMemDC(), font);
	wsprintf(str, "상하 방향키로 선택, 좌우 방향키로 맵 크기 조절, ENTER키로 맵 생성");
	wsprintf(widthStr, "가로 : %d", _tileX);
	wsprintf(heightStr, "세로 : %d", _tileY);
	TextOut(getMemDC(), 50, 50, str, strlen(str));
	TextOut(getMemDC(), 200, 300, widthStr, strlen(widthStr));
	TextOut(getMemDC(), 200, 330, heightStr, strlen(heightStr));
	SelectObject(getMemDC(), oldFont);
	DeleteObject(font);

	if(_input == WIDTH) EllipseMakeCenter(getMemDC(), 150, 312, 25, 25);
	else EllipseMakeCenter(getMemDC(), 150, 342, 25, 25);
}
