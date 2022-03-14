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
	font = CreateFont(25, 0, 0, 0, 60, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("�޸ձ���"));
	oldFont = (HFONT)SelectObject(getMemDC(), font);
	wsprintf(str, "���� ����Ű�� ����, �¿� ����Ű�� �� ũ�� ����, ENTERŰ�� �� ����");
	wsprintf(widthStr, "���� : %d", _tileX);
	wsprintf(heightStr, "���� : %d", _tileY);
	TextOut(getMemDC(), 50, 50, str, strlen(str));
	TextOut(getMemDC(), 200, 300, widthStr, strlen(widthStr));
	TextOut(getMemDC(), 200, 330, heightStr, strlen(heightStr));
	SelectObject(getMemDC(), oldFont);
	DeleteObject(font);

	if(_input == WIDTH) EllipseMakeCenter(getMemDC(), 150, 312, 25, 25);
	else EllipseMakeCenter(getMemDC(), 150, 342, 25, 25);
}
