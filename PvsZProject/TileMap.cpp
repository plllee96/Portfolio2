#include "Stdafx.h"
#include "TileMap.h"

HRESULT TileMap::init(unsigned short x, unsigned short y) {
	_x = x;
	_y = y;
	
	for (int i = 0; i < x*y; i++) {
		tagTile tile;
		tile.x = x;
		tile.y = y;
		tile.rc = RectMake(TOPLEFT_X + (i % x) * TILESIZE, TOPLEFT_Y + (i / x) * TILESIZE, TILESIZE, TILESIZE);
		_vTile.push_back(tile);
	}

	_object = new TileObject;
	_object->init(OBJECT_AMOUNT, x, y);

	return S_OK;
}

void TileMap::release(void) {

}

void TileMap::update(void) {
	_object->update();
}

void TileMap::render(void) {
	HFONT font;
	HFONT oldFont;

	char str[128];
	char widthStr[128];
	char heightStr[128];
	font = CreateFont(25, 0, 0, 0, 60, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("ÈÞ¸Õ±¼¸²"));
	oldFont = (HFONT)SelectObject(getMemDC(), font);
	wsprintf(str, "Q Å°·Î µÚ·Î°¡±â");
	TextOut(getMemDC(), 50, 50, str, strlen(str));
	SelectObject(getMemDC(), oldFont);
	DeleteObject(font);

	for (auto tile : _vTile) {
		Rectangle(getMemDC(), tile.rc.left, tile.rc.top, tile.rc.right, tile.rc.bottom);
	}
	_object->render();
}
