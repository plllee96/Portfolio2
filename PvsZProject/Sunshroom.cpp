#include "Stdafx.h"
#include "Sunshroom.h"

HRESULT Sunshroom::init(PlantType type, POINT location) {
	Plant::init(type, location);
	_image = IMAGEMANAGER->addFrameImage("SunShroom", "Resources/Images/Plants/SunShroom.bmp", 240, 100, 5, 2, true, RGB(255, 0, 255));
	_rc = _recognizeRc = RectMake(startX + _location.x * tileWidth, startY + _location.y * _tileHeight, tileWidth, _tileHeight);
	_status = SunshroomStatus::WAIT;

	_generateCooltime = 10.0f;
	_generateCount = TIMEMANAGER->getWorldTime();
	_generate = false;

	_growTime = 35.0f;
	_growCount = TIMEMANAGER->getWorldTime();
	_grow = false;

	_frame.maxFrameX = 5;
	_frame.coolTime = 0.5f;

	return S_OK;
}

void Sunshroom::release(void) {
	Plant::release();
}

void Sunshroom::update(void) {
	Plant::update();
	act();
	setFrame();
	updateFrame();
}

void Sunshroom::render(void) {
	_image->frameRender(getMemDC(), _rc.left, _rc.top, _frame.currentFrameX, _frame.currentFrameY);
}

void Sunshroom::act() {
	if (_generateCooltime + _generateCount <= TIMEMANAGER->getWorldTime()) {
		_generate = true;
		_generateCount = TIMEMANAGER->getWorldTime();
	}

	if (_growTime + _growCount <= TIMEMANAGER->getWorldTime()) {
		_grow = true;
	}
}

void Sunshroom::setFrame() {
	//! Do Nothing
}

void Sunshroom::updateFrame() {
	(_grow) ? _frame.currentFrameY = 1 : _frame.currentFrameY = 0;

	if (_frame.count + _frame.coolTime < TIMEMANAGER->getWorldTime()) {
		_frame.count = TIMEMANAGER->getWorldTime();

		if (_frame.currentFrameX >= _frame.maxFrameX - 1) {
			_frame.currentFrameX = 0;
		}
		else _frame.currentFrameX += 1;
	}
}

RECT Sunshroom::getRect() {
	RECT temp;
	temp.left = _rc.left + 25;
	temp.top = _rc.top + 30;
	return temp;
}
