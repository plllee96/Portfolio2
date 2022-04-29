#include "Stdafx.h"
#include "TwinSunflower.h"

HRESULT TwinSunflower::init(PlantType type, POINT location) {
	Plant::init(type, location);
	_image = IMAGEMANAGER->addFrameImage("TwinSunflower", "Resources/Images/Plants/TwinSunflower.bmp", 1000, 82, 10, 1, true, RGB(255, 0, 255));
	_rc = _recognizeRc = RectMake(startX + _location.x * tileWidth, startY + _location.y * _tileHeight, tileWidth, _tileHeight);
	_status = TwinSunflowerStatus::WAIT;

	_generateCooltime = 10.0f;
	_generateCount = TIMEMANAGER->getWorldTime();
	_generate = false;

	return S_OK;
}

void TwinSunflower::release(void) {
	Plant::release();
}

void TwinSunflower::update(void) {
	Plant::update();
	act();
	setFrame();
	updateFrame();
}

void TwinSunflower::render(void) {
	Plant::render();
	_image->frameRender(getMemDC(), _rc.left - 20, _rc.top - 20, _frame.currentFrameX, _frame.currentFrameY);
}

void TwinSunflower::act() {
	if (_generateCooltime + _generateCount <= TIMEMANAGER->getWorldTime()) {
		_generate = true;
		_generateCount = TIMEMANAGER->getWorldTime();
	}
}

void TwinSunflower::setFrame() {
	switch (_status) {
		case TwinSunflowerStatus::WAIT: {
			_frame.maxFrameX = 8;
			_frame.coolTime = 0.1f;
			_frame.currentFrameY = 10;
		} break;
		case TwinSunflowerStatus::GENERATE: {
			_frame.maxFrameX = 1;
			_frame.coolTime = 0.1f;
			_frame.currentFrameY = 1;
		} break;
	}
}

void TwinSunflower::updateFrame() {
	if (_frame.count + _frame.coolTime < TIMEMANAGER->getWorldTime()) {
		_frame.count = TIMEMANAGER->getWorldTime();

		if (_frame.currentFrameX >= _frame.maxFrameX - 1) {
			_frame.currentFrameX = 0;
		}
		else _frame.currentFrameX += 1;
	}
}

RECT TwinSunflower::getRect() {
	RECT temp;
	temp.left = _rc.left + 25;
	temp.top = _rc.top + 30;
	return temp;
}
