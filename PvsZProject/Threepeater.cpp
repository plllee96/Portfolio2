#include "Stdafx.h"
#include "Threepeater.h"

HRESULT Threepeater::init(PlantType type, POINT location) {
	Plant::init(type, location);
	_image = IMAGEMANAGER->addFrameImage("Threepeater", "Resources/Images/Plants/Threepeater.bmp", 704, 148, 8, 2, true, RGB(255, 0, 255));
	_rc = RectMake(startX + _location.x * tileWidth, startY + _location.y * _tileHeight, tileWidth, _tileHeight);
	_recognizeRc = RectMake(startX + _location.x * tileWidth + (tileWidth / 2), (startY + _location.y * _tileHeight) - _tileHeight, WINSIZE_X, _tileHeight * 3);
	_status = ThreepeaterStatus::WAIT;
	_bulletType = BulletType::THREEPEATER_BULLET;

	fixFireX = 25;
	fixFireY = -10;

	_shotCount = TIMEMANAGER->getWorldTime();
	_shotCooltime = 1.5f;
	_alreadyShot = false;

	_fireX = _rc.left + fixFireX;
	_fireY = _rc.top + fixFireY;

	return S_OK;
}

void Threepeater::release(void) {
	Plant::release();
}

void Threepeater::update(void) {
	Plant::update();
	setFrame();
	updateFrame();
}

void Threepeater::render(void) {
	_image->frameRender(getMemDC(), _rc.left - 18, _rc.top - 10, _frame.currentFrameX, _frame.currentFrameY);
}

void Threepeater::act() {
	if (_status == ThreepeaterStatus::SHOT) {
		if (_frame.currentFrameX == 1 && !_alreadyShot) {
			_alreadyShot = true;
			fire(true);
		}
		else fire(false);
	}
}

void Threepeater::fire(bool fire) {
	_fire = fire;
}

void Threepeater::recognizeObject(ObserveData observer) {
	if (_shotCooltime + _shotCount < TIMEMANAGER->getWorldTime()) {
		_status = ThreepeaterStatus::SHOT;
		_frame.currentFrameX = 0;
		_shotCount = TIMEMANAGER->getWorldTime();
	}
}

void Threepeater::setFrame() {
	switch (_status) {
		case ThreepeaterStatus::WAIT: {
			_frame.maxFrameX = 8;
			_frame.coolTime = 0.5f;
			_frame.currentFrameY = 0;
		} break;
		case ThreepeaterStatus::SHOT: {
			_frame.maxFrameX = 2;
			_frame.coolTime = 0.1f;
			_frame.currentFrameY = 1;
		} break;
	}
}

void Threepeater::updateFrame() {
	if (_frame.count + _frame.coolTime < TIMEMANAGER->getWorldTime()) {
		_frame.count = TIMEMANAGER->getWorldTime();
		if (_frame.currentFrameX >= _frame.maxFrameX - 1) {
			if (_status == ThreepeaterStatus::SHOT) {
				_status = ThreepeaterStatus::WAIT;
				_alreadyShot = false;
			}
			_frame.currentFrameX = 0;
		}
		else _frame.currentFrameX += 1;
	}
}
