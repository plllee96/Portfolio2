#include "Stdafx.h"
#include "Tile.h"

HRESULT Tile::init(int stageNum) {
	_image = IMAGEMANAGER->addFrameImage("Tomb", "Resources/Images/Objects/Tomb.bmp", 512, 80, 8, 1, true, RGB(255, 0, 255));
	_fogImage = IMAGEMANAGER->addImage("Fog", "Resources/Images/Objects/Fog.bmp", 98, 80, true, RGB(255, 0, 255));
	
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
		else temp.rc = RectMake(startX + (i%_column) * tileWidth, startY + (i / _column) * secondMapTileHeight, tileWidth, secondMapTileHeight);
		temp.hasPlant = false;
		temp.hasObstacle = false;
		temp.isWater = false;
		if (_row == 6) {
			if ((i / _column) == 2 || (i / _column) == 3) temp.isWater = true;
		}
		temp.hasLilypad = false;
		temp.tombType = RND->getInt(8);
		_vTile.push_back(temp);
	}

	for (int i = 0; i < 8 * 7; i++) {
		SingleFog fog;
		fog.x = i % 7;
		fog.y = i / 7;
		fog.startX = 350 + fog.x * 50;
		fog.moveX = 0;
		fog.rc = RectMake(350 + fog.x * 50, fog.y * 50, _fogImage->getWidth() , _fogImage->getHeight());
		fog.blown = false;
		fog.lantern = false;
		fog.alpha = 0;
		_vFog.push_back(fog);
	}

	if (stageNum == 1) setNightObstacle(5);

	return S_OK;
}

void Tile::release(void) {
}

void Tile::update(void) {
	for (int j = 0; j < _vFog.size(); j++) {
		bool temp = false;

		for (int i = 0; i < _lanternRc.size(); i++) {		
			RECT tempRc;
			if (IntersectRect(&tempRc, &_vFog[j].rc, &_lanternRc[i])) {
				temp = true;
			}
		}

		(temp) ? _vFog[j].lantern = true : _vFog[j].lantern = false;
	}
	for (int i = 0; i < _vFog.size(); i++) {
		if (_vFog[i].lantern) {
			if (_vFog[i].alpha > 0) _vFog[i].alpha--;
		}
		else {
			if (_vFog[i].alpha < 255) _vFog[i].alpha++;
		}
	}

	for (int i = 0; i < _vFog.size(); i++) {
		if (_vFog[i].blown) {
			_vFog[i].moveX += 10;
		}
		else {
			if (_vFog[i].moveX > 0) {
				_vFog[i].moveX --;
			}
		}
		_vFog[i].rc = RectMake(200 + _vFog[i].x * 50 + _vFog[i].moveX, _vFog[i].y * 50, _fogImage->getWidth(), _fogImage->getHeight());
	}

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
		if (num == 5) {
			while (tempY == 2 || tempY == 3) {
				tempY = RND->getInt(_row);
			}
		}
		int tempPosition = _column * tempY + tempX;
		if (!getTile(tempPosition).hasObstacle) {
			setObstacle(tempPosition, true);
			tempNum--;
		}
	}
}

void Tile::setFog(RECT rc) {
	_lanternRc.push_back(rc);
}

void Tile::removePlantern(RECT rc) {
	for (int i = 0; i < _lanternRc.size(); i++) {
		if (_lanternRc[i].left == rc.left && _lanternRc[i].top == rc.top
			&& _lanternRc[i].right == rc.right && _lanternRc[i].bottom == rc.bottom) {
			_lanternRc.erase(_lanternRc.begin() + i);
			break;
		}
	}
}

void Tile::blowFog(bool blow) {
	for (int i = 0; i < _vFog.size(); i++) {
		_vFog[i].blown = blow;
	}
}

void Tile::printFog() {
	for (auto iter : _vFog) {
		_fogImage->alphaRender(getMemDC(), iter.rc.left, iter.rc.top, iter.alpha);
	}
}
