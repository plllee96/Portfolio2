#include "Stdafx.h"
#include "Puffshroom.h"

HRESULT Puffshroom::init(PlantType type, POINT location) {
	Plant::init(type, location);
	_image = IMAGEMANAGER->addFrameImage("Puffshroom", "Resources/Images/Plants/PuffShroom.bmp", 144, 72, 4, 2, true, RGB(255, 0, 255));
	_rc = RectMake(startX + _location.x * tileWidth, startY + _location.y * _tileHeight, tileWidth, _tileHeight);
	_recognizeRc = RectMake(startX + _location.x * tileWidth + (tileWidth / 2), startY + _location.y * _tileHeight, tileWidth*3.5, _tileHeight);
	_status = PuffshroomStatus::WAIT;
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

void Puffshroom::release(void) {
	Plant::release();
}

void Puffshroom::update(void) {
	Plant::update();
	setFrame();
	updateFrame();
}

void Puffshroom::render(void) {
	_image->frameRender(getMemDC(), _rc.left, _rc.top + 20, _frame.currentFrameX, _frame.currentFrameY);
}

void Puffshroom::act() {
	if (_status == PuffshroomStatus::SHOT) {
		if (_frame.currentFrameX == 1 && !_alreadyShot) {
			_alreadyShot = true;
			fire(true);
		}
		else fire(false);
	}
}

void Puffshroom::fire(bool fire) {
	_fire = fire;
}

void Puffshroom::recognizeObject(ObserveData observer) {
	if (_shotCooltime + _shotCount < TIMEMANAGER->getWorldTime()) {
		_status = PuffshroomStatus::SHOT;
		_frame.currentFrameX = 0;
		_shotCount = TIMEMANAGER->getWorldTime();
	}
}

void Puffshroom::setFrame() {
	switch (_status) {
		case PuffshroomStatus::WAIT: {
			_frame.maxFrameX = 4;
			_frame.coolTime = 0.1f;
			_frame.currentFrameY = 0;
		} break;
		case PuffshroomStatus::SHOT: {
			_frame.maxFrameX = 4;
			_frame.coolTime = 0.1f;
			_frame.currentFrameY = 1;
		} break;
	}
}

void Puffshroom::updateFrame() {
	if (_frame.count + _frame.coolTime < TIMEMANAGER->getWorldTime()) {
		_frame.count = TIMEMANAGER->getWorldTime();
		if (_frame.currentFrameX >= _frame.maxFrameX - 1) {
			if (_status == PuffshroomStatus::SHOT) {
				_status = PuffshroomStatus::WAIT;
				_alreadyShot = false;
			}
			_frame.currentFrameX = 0;
		}
		else _frame.currentFrameX += 1;
	}
}
