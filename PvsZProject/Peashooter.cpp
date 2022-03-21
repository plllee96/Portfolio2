#include "Stdafx.h"
#include "Peashooter.h"
#include "BulletManager.h"

HRESULT Peashooter::init(PlantType type, POINT location) {
	Plant::init(type, location);
	_image = IMAGEMANAGER->addFrameImage("Peashooter", "Resources/Images/Plants/Peashooter.bmp", 432, 128, 8, 2, true, RGB(255, 0, 255));
	_rc = RectMake(startX + _location.x * tileWidth, startY + _location.y * firstMapTileHeight, tileWidth, firstMapTileHeight);
	_recognizeRc = RectMake(startX + _location.x * tileWidth + (tileWidth / 2), startY + _location.y * firstMapTileHeight, WINSIZE_X, firstMapTileHeight);
	_status = PeashooterStatus::WAIT;

	_shotCount = TIMEMANAGER->getWorldTime();
	_shotCooltime = 1.5f;
	_alreadyShot = false;

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
			fire();
		}
	}
}

void Peashooter::fire() {
	//옵저버 전송
}

ObserveData Peashooter::getRectUpdate() {
	ObserveData temp;
	temp.rc = &_rc;
	temp.recognizeRc = &_recognizeRc;
	temp.type = &_obType;
	return temp;
}

void Peashooter::collideObject(ObserveData obData) {
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
			_frame.coolTime = 0.5f;
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
