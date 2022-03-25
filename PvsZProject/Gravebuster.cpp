#include "Stdafx.h"
#include "Gravebuster.h"

HRESULT Gravebuster::init(PlantType type, POINT location) {
	Plant::init(type, location);
	_image = IMAGEMANAGER->addFrameImage("Gravebuster", "Resources/Images/Plants/GraveBuster.bmp", 312, 76, 4, 1, true, RGB(255, 0, 255));
	_startRc = _rc = _recognizeRc = RectMake(startX + _location.x * tileWidth, startY + _location.y * firstMapTileHeight, tileWidth, firstMapTileHeight);

	_frame.maxFrameX = 4;
	_frame.coolTime = 0.25f;
	_frame.currentFrameY = 0;
	_moveY = 0.0f;
	return S_OK;
}

void Gravebuster::release(void) {
	Plant::release();
}

void Gravebuster::update(void) {
	Plant::update();
	updateFrame();

	_rc.top = _startRc.top + _moveY;
	_rc.bottom = _startRc.bottom + _moveY;
	_moveY += 0.02f;

	if (_rc.top - _startRc.top > 10.0f) _active = false;
}

void Gravebuster::render(void) {
	_image->frameRender(getMemDC(), _rc.left - 16, _rc.top - 20, _frame.currentFrameX, _frame.currentFrameY);
}

void Gravebuster::updateFrame() {
	if (_frame.count + _frame.coolTime < TIMEMANAGER->getWorldTime()) {
		_frame.count = TIMEMANAGER->getWorldTime();
		if (_frame.currentFrameX >= _frame.maxFrameX - 1) {
			_frame.currentFrameX = 0;
		}
		_frame.currentFrameX += 1;
	}
}
