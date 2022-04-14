#include "Stdafx.h"
#include "Seashroom.h"

HRESULT Seashroom::init(PlantType type, POINT location) {
	Plant::init(type, location);
	_image = IMAGEMANAGER->addFrameImage("SeaShroom", "Resources/Images/Plants/SeaShroom.bmp", 80, 88, 2, 2, true, RGB(255, 0, 255));
	_rc = RectMake(startX + _location.x * tileWidth, startY + _location.y * _tileHeight, tileWidth, _tileHeight);
	_recognizeRc = RectMake(startX + _location.x * tileWidth + (tileWidth / 2), startY + _location.y * _tileHeight, tileWidth*3.5, _tileHeight);
	_status = SeashroomStatus::WAIT;
	_bulletType = BulletType::MUSHROOM_BULLET;

	fixFireX = 25;
	fixFireY = 20;

	_shotCount = TIMEMANAGER->getWorldTime();
	_shotCooltime = 1.5f;
	_alreadyShot = false;

	_fireX = _rc.left + fixFireX;
	_fireY = _rc.top + fixFireY;

	return S_OK;
}

void Seashroom::release(void) {
	Plant::release();
}

void Seashroom::update(void) {
	Plant::update();
	setFrame();
	updateFrame();
}

void Seashroom::render(void) {
	_image->frameRender(getMemDC(), _rc.left, _rc.top + 20, _frame.currentFrameX, _frame.currentFrameY);
}

void Seashroom::act() {
	if (_status == SeashroomStatus::SHOT) {
		if (_frame.currentFrameX == 1 && !_alreadyShot) {
			_alreadyShot = true;
			fire(true);
		}
		else fire(false);
	}
}

void Seashroom::fire(bool fire) {
	_fire = fire;
}

void Seashroom::recognizeObject(ObserveData observer) {
	if (_shotCooltime + _shotCount < TIMEMANAGER->getWorldTime()) {
		_status = SeashroomStatus::SHOT;
		_frame.currentFrameX = 0;
		_shotCount = TIMEMANAGER->getWorldTime();
	}
}

void Seashroom::setFrame() {
	switch (_status) {
		case SeashroomStatus::WAIT: {
			_frame.maxFrameX = 2;
			_frame.coolTime = 0.5f;
			_frame.currentFrameY = 0;
		} break;
		case SeashroomStatus::SHOT: {
			_frame.maxFrameX = 2;
			_frame.coolTime = 0.1f;
			_frame.currentFrameY = 1;
		} break;
	}
}

void Seashroom::updateFrame() {
	if (_frame.count + _frame.coolTime < TIMEMANAGER->getWorldTime()) {
		_frame.count = TIMEMANAGER->getWorldTime();
		if (_frame.currentFrameX >= _frame.maxFrameX - 1) {
			if (_status == SeashroomStatus::SHOT) {
				_status = SeashroomStatus::WAIT;
				_alreadyShot = false;
			}
			_frame.currentFrameX = 0;
		}
		else _frame.currentFrameX += 1;
	}
}
