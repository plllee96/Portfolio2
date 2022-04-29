#include "Stdafx.h"
#include "Peashooter.h"
#include "BulletManager.h"

HRESULT Peashooter::init(PlantType type, POINT location) {
	Plant::init(type, location);
	_image = IMAGEMANAGER->addFrameImage("Peashooter", "Resources/Images/Plants/Peashooter.bmp", 480, 128, 8, 2, true, RGB(255, 0, 255));
	_rc = RectMake(startX + _location.x * tileWidth, startY + _location.y * _tileHeight, tileWidth, _tileHeight);
	_recognizeRc = RectMake(startX + _location.x * tileWidth + (tileWidth / 2), startY + _location.y * _tileHeight, WINSIZE_X, _tileHeight);
	_status = PeashooterStatus::WAIT;
	_bulletType = BulletType::PEASHOOTER_BULLET;

	fixFireX = 45;
	fixFireY = -2;

	_shotCount = TIMEMANAGER->getWorldTime();
	_shotCooltime = 1.5f;
	_alreadyShot = false;

	_fireX = _rc.left + fixFireX;
	_fireY = _rc.top + fixFireY;

	return S_OK;
}

void Peashooter::release(void) {
	Plant::release();
}

void Peashooter::update(void) {
	Plant::update();
	setFrame();
	updateFrame();
}

void Peashooter::render(void) {
	_image->frameRender(getMemDC(), _rc.left, _rc.top, _frame.currentFrameX, _frame.currentFrameY);
}

void Peashooter::act() {
	if (_status == PeashooterStatus::SHOT) {
		if (_frame.currentFrameX == 1 && !_alreadyShot) {
			_alreadyShot = true;
			fire(true);
		}
		else fire(false);
	}
}

void Peashooter::fire(bool fire) {
	_fire = fire;
}

void Peashooter::recognizeObject(ObserveData observer) {
	if (_shotCooltime + _shotCount < TIMEMANAGER->getWorldTime()) {
		_status = PeashooterStatus::SHOT;
		_frame.currentFrameX = 0;
		_shotCount = TIMEMANAGER->getWorldTime();
	}
}


void Peashooter::setFrame() {
	switch (_status) {
		case PeashooterStatus::WAIT: {
			_frame.maxFrameX = 8;
			_frame.coolTime = 0.1f;
			_frame.currentFrameY = 0;
		} break;
		case PeashooterStatus::SHOT: {
			_frame.maxFrameX = 3;
			_frame.coolTime = 0.1f;
			_frame.currentFrameY = 1;
		} break;
	}
}

void Peashooter::updateFrame() {
	if (_frame.count + _frame.coolTime < TIMEMANAGER->getWorldTime()) {
		_frame.count = TIMEMANAGER->getWorldTime();
		if (_frame.currentFrameX >= _frame.maxFrameX - 1) {
			if (_status == PeashooterStatus::SHOT) {
				_status = PeashooterStatus::WAIT;
				_alreadyShot = false;
			}
			_frame.currentFrameX = 0;
		}
		else _frame.currentFrameX+= 1;
	}
}
