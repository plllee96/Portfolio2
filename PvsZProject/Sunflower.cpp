#include "Stdafx.h"
#include "Sunflower.h"

HRESULT Sunflower::init(PlantType type, POINT location) {
	Plant::init(type, location);
	_image = IMAGEMANAGER->addFrameImage("Sunflower", "Resources/Images/Plants/Sunflower.bmp", 464, 128, 8, 2, true, RGB(255, 0, 255));
	_rc = _recognizeRc = RectMake(startX + _location.x * tileWidth, startY + _location.y * firstMapTileHeight, tileWidth, firstMapTileHeight);
	_status = SunflowerStatus::WAIT;

	_generateCooltime = 10.0f;
	_generateCount = TIMEMANAGER->getWorldTime();
	_generate = false;

	return S_OK;
}

void Sunflower::release(void) {
	Plant::release();
}

void Sunflower::update(void) {
	Plant::update();
	act();
	setFrame();
	updateFrame();
}

void Sunflower::render(void) {
	Plant::render();
	_image->frameRender(getMemDC(), _rc.left, _rc.top, _frame.currentFrameX, _frame.currentFrameY);
}

void Sunflower::act() {
	if (_generateCooltime + _generateCount <= TIMEMANAGER->getWorldTime()) {
		_generate = true;
		_generateCount = TIMEMANAGER->getWorldTime();
	}
}

void Sunflower::setFrame() {
	switch (_status) {
		case SunflowerStatus::WAIT: {
			_frame.maxFrameX = 8;
			_frame.coolTime = 0.5f;
			_frame.currentFrameY = 0;
		} break;
		case SunflowerStatus::GENERATE: {
			_frame.maxFrameX = 1;
			_frame.coolTime = 0.5f;
			_frame.currentFrameY = 1;
		} break;
	}
}

void Sunflower::updateFrame() {
	if (_frame.count + _frame.coolTime < TIMEMANAGER->getWorldTime()) {
		_frame.count = TIMEMANAGER->getWorldTime();

		if (_frame.currentFrameX >= _frame.maxFrameX - 1) {
			_frame.currentFrameX = 0;
		}
		else _frame.currentFrameX += 1;
	}
}

RECT Sunflower::getRect() {
	RECT temp;
	temp.left = _rc.left + 25;
	temp.top = _rc.top + 30;
	return temp;
}
