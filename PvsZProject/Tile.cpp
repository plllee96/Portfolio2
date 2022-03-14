#include "Stdafx.h"
#include "Tile.h"

HRESULT Tile::init(void) {
	_tilemenu = SETTING;
	_tileSetting = new TileSetting;
	_tileSetting->init();
	_tileMap = new TileMap;
	return S_OK;
}

void Tile::release(void) {
	if (_tileSetting) _tileSetting->release();
	SAFE_DELETE(_tileSetting);
	if (_tileMap) _tileMap->release();
	SAFE_DELETE(_tileMap);
}

void Tile::update(void) {
	if (_tilemenu == SETTING) {
		_tileSetting->update();
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN)) {
			if (!_tileMap) {
				_tileMap = new TileMap;
			}
			_tileMap->init(_tileSetting->getX(), _tileSetting->getY());
			_tileSetting->release();
			SAFE_DELETE(_tileSetting);
			_tilemenu = MAP;
		}
	}
	else if (_tilemenu == MAP) {
		_tileMap->update();
		if (KEYMANAGER->isOnceKeyDown('Q')) {
			if (!_tileSetting) {
				_tileSetting = new TileSetting;
			}
			_tileSetting->init();
			_tileMap->release();
			SAFE_DELETE(_tileMap);
			_tilemenu = SETTING;
		}
	}
}

void Tile::render(void) {
	if (_tilemenu == SETTING) {
		_tileSetting->render();
	}
	else if (_tilemenu == MAP) {
		_tileMap->render();
	}
}
