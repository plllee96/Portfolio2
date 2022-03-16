#include "Stdafx.h"
#include "Tile.h"

HRESULT Tile::init(int stageNum) {

	if (_vTile.size() != 0) _vTile.clear();
	_column = 9;
	switch (stageNum) {
		case 0: _row = 5; break;
		case 1: _row = 5; break;
		case 2: _row = 6; break;
		case 3: _row = 6; break;
	}
	for (int i = 0; i < _row * _column; i++) {
		SingleTile temp;
		if (_row == 5) temp.rc = RectMake(startX + (i%_column) * tileWidth, startY + (i/_column) * firstMapTileHeight, tileWidth, firstMapTileHeight);
		else temp.rc = RectMake(startX + (i%_column) * tileWidth, startY + (i / _column) * firstMapTileHeight, tileWidth, firstMapTileHeight);
		temp.hasPlant = false;
		_vTile.push_back(temp);
	}
	return S_OK;
}

void Tile::release(void) {
}

void Tile::update(void) {
}

void Tile::render(void) {
	for (auto iter : _vTile) {
		if (iter.hasPlant) Rectangle(getMemDC(), iter.rc.left, iter.rc.top, iter.rc.right, iter.rc.bottom);
	}
}

int Tile::selectTile() {
	for (int i = 0; i < _vTile.size(); i++) {
		if (PtInRect(&(_vTile[i].rc), _ptMouse)) {
			return i;
		}
	}
	return -1;
}
