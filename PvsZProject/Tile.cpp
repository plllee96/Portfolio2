#include "Stdafx.h"
#include "Tile.h"

HRESULT Tile::init(int stageNum) {
	_image = IMAGEMANAGER->addFrameImage("Tomb", "Resources/Images/Objects/Tomb.bmp", 512, 80, 8, 1, true, RGB(255, 0, 255));

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
		temp.x = i % _column;
		temp.y = i / _column;
		if (_row == 5) temp.rc = RectMake(startX + (i%_column) * tileWidth, startY + (i/_column) * firstMapTileHeight, tileWidth, firstMapTileHeight);
		else temp.rc = RectMake(startX + (i%_column) * tileWidth, startY + (i / _column) * firstMapTileHeight, tileWidth, firstMapTileHeight);
		temp.hasPlant = false;
		temp.hasObstacle = false;
		temp.isWater = false;
		temp.hasLilypad = false;
		temp.tombType = RND->getInt(8);
		_vTile.push_back(temp);
	}

	if (stageNum == 1) setNightObstacle(4);
	else if (stageNum == 3) setNightObstacle(6);

	return S_OK;
}

void Tile::release(void) {
}

void Tile::update(void) {
}

void Tile::render(void) {
	for (auto iter : _vTile) {
		if (iter.hasObstacle) {
			_image->frameRender(getMemDC(), iter.rc.left - 8, iter.rc.top - 2, iter.tombType, 0);
		}
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

void Tile::setNightObstacle(int num) {
	int tempNum = num;

	while (tempNum > 0) {
		int tempX = RND->getFromIntTo(5, 8);
		int tempY = RND->getInt(_row);
		int tempPosition = _column * tempY + tempX;
		if (!getTile(tempPosition).hasObstacle) {
			setObstacle(tempPosition, true);
			tempNum--;
		}
	}
}
