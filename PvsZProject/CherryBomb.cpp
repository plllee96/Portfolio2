#include "Stdafx.h"
#include "CherryBomb.h"

HRESULT CherryBomb::init(PlantType type, POINT location) {
	Plant::init(type, location);
	_image = IMAGEMANAGER->addFrameImage("CherryBomb", "Resources/Images/Plants/CherryBomb.bmp", 600, 76, 6, 1, true, RGB(255, 0, 255));
	_rc = _recognizeRc = RectMake(startX + _location.x * tileWidth - 25, startY + _location.y * _tileHeight, tileWidth, _tileHeight);

	_bulletType = BulletType::CHERRY_EXPLODE;

	_fireX = _rc.left - 50;
	_fireY = _rc.top - 30;

	_frame.maxFrameX = 6;
	_frame.coolTime = 0.16f;
	_frame.currentFrameY = 0;
	return S_OK;
}

void CherryBomb::release(void) {
	Plant::release();
}

void CherryBomb::update(void) {
	if (_fire) _active = false;
	updateFrame();
}

void CherryBomb::render(void) {
	_image->frameRender(getMemDC(), _rc.left, _rc.top, _frame.currentFrameX, _frame.currentFrameY);
}

void CherryBomb::updateFrame() {
	if (_frame.count + _frame.coolTime < TIMEMANAGER->getWorldTime()) {
		_frame.count = TIMEMANAGER->getWorldTime();
		if (_frame.currentFrameX > _frame.maxFrameX) {
			_fire = true;
		}
		_frame.currentFrameX += 1;
	}
}
