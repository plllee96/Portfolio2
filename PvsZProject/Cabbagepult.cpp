#include "Stdafx.h"
#include "Cabbagepult.h"

HRESULT Cabbagepult::init(PlantType type, POINT location) {
	Plant::init(type, location);
	_image = IMAGEMANAGER->addFrameImage("Cabbagepult", "Resources/Images/Plants/Cabbagepult.bmp", 720, 196, 8, 2, true, RGB(255, 0, 255));
	_rc = RectMake(startX + _location.x * tileWidth, startY + _location.y * _tileHeight, tileWidth, _tileHeight);
	_recognizeRc = RectMake(startX + _location.x * tileWidth + (tileWidth / 2), startY + _location.y * _tileHeight, WINSIZE_X, _tileHeight);
	_status = CabbageStatus::WAIT;
	_bulletType = BulletType::CABBAGEPULT_BULLET;

	fixFireX = 45;
	fixFireY = -2;

	_shotCount = TIMEMANAGER->getWorldTime();
	_shotCooltime = 3.0f;
	_alreadyShot = false;

	_fireX = _rc.left + fixFireX;
	_fireY = _rc.top + fixFireY;

	_recogZombieRC = { 0,0,0,0 };

	return S_OK;
}

void Cabbagepult::release(void) {
	Plant::release();
}

void Cabbagepult::update(void) {
	Plant::update();
	setFrame();
	updateFrame();
}

void Cabbagepult::render(void) {
	_image->frameRender(getMemDC(), _rc.left - 35, _rc.top - 35, _frame.currentFrameX, _frame.currentFrameY);
}

void Cabbagepult::act() {
	if (_status == CabbageStatus::SHOT) {
		if (_frame.currentFrameX == 3 && !_alreadyShot) {
			_alreadyShot = true;
			fire(true);
		}
		else fire(false);
	}
}

void Cabbagepult::fire(bool fire) {
	_fire = fire;
}

void Cabbagepult::recognizeObject(ObserveData observer) {
	if (_shotCooltime + _shotCount < TIMEMANAGER->getWorldTime()) {
		_status = CabbageStatus::SHOT;
		_frame.currentFrameX = 0;
		_shotCount = TIMEMANAGER->getWorldTime();
		_recogZombieRC = (*observer.rc);
	}
}

void Cabbagepult::setFrame() {
	switch (_status) {
		case CabbageStatus::WAIT: {
			_frame.maxFrameX = 6;
			_frame.coolTime = 0.5f;
			_frame.currentFrameY = 0;
		} break;
		case CabbageStatus::SHOT: {
			_frame.maxFrameX = 8;
			_frame.coolTime = 0.05f;
			_frame.currentFrameY = 1;
		} break;
	}
}

void Cabbagepult::updateFrame() {
	if (_frame.count + _frame.coolTime < TIMEMANAGER->getWorldTime()) {
		_frame.count = TIMEMANAGER->getWorldTime();
		if (_frame.currentFrameX >= _frame.maxFrameX - 1) {
			if (_status == CabbageStatus::SHOT) {
				_status = CabbageStatus::WAIT;
				_alreadyShot = false;
			}
			_frame.currentFrameX = 0;
		}
		else _frame.currentFrameX += 1;
	}
}
