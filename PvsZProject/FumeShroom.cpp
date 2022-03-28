#include "Stdafx.h"
#include "FumeShroom.h"

HRESULT FumeShroom::init(PlantType type, POINT location) {
	Plant::init(type, location);
	_image = IMAGEMANAGER->addFrameImage("FumeShroom", "Resources/Images/Plants/FumeShroom.bmp", 376, 156, 4, 2, true, RGB(255, 0, 255));
	_rc = RectMake(startX + _location.x * tileWidth, startY + _location.y * _tileHeight, tileWidth, _tileHeight);
	_recognizeRc = RectMake(startX + _location.x * tileWidth + (tileWidth / 2), startY + _location.y * _tileHeight, tileWidth*5, _tileHeight);
	_status = FumeshroomStatus::WAIT;
	_bulletType = BulletType::FUMESHROOM_BULLET;

	fixFireX = 57;
	fixFireY = -12;

	_shotCount = TIMEMANAGER->getWorldTime();
	_shotCooltime = 1.5f;
	_alreadyShot = false;

	_fireX = _rc.left + fixFireX;
	_fireY = _rc.top + fixFireY;

	return S_OK;
}

void FumeShroom::release(void) {
	Plant::release();
}

void FumeShroom::update(void) {
	Plant::update();
	setFrame();
	updateFrame();
}

void FumeShroom::render(void) {
	_image->frameRender(getMemDC(), _rc.left - 20, _rc.top - 10, _frame.currentFrameX, _frame.currentFrameY);
}

void FumeShroom::act() {
	if (_status == FumeshroomStatus::SHOT) {
		if (_frame.currentFrameX == 2 && !_alreadyShot) {
			_alreadyShot = true;
			fire(true);
		}
		else fire(false);
	}
}

void FumeShroom::fire(bool fire) {
	_fire = fire;
}

void FumeShroom::recognizeObject(ObserveData observer) {
	if (_shotCooltime + _shotCount < TIMEMANAGER->getWorldTime()) {
		_status = FumeshroomStatus::SHOT;
		_frame.currentFrameX = 0;
		_shotCount = TIMEMANAGER->getWorldTime();
	}
}
void FumeShroom::setFrame() {
	switch (_status) {
		case FumeshroomStatus::WAIT: {
			_frame.maxFrameX = 4;
			_frame.coolTime = 0.5f;
			_frame.currentFrameY = 0;
		} break;
		case FumeshroomStatus::SHOT: {
			_frame.maxFrameX = 4;
			_frame.coolTime = 0.1f;
			_frame.currentFrameY = 1;
		} break;
	}
}

void FumeShroom::updateFrame() {
	if (_frame.count + _frame.coolTime < TIMEMANAGER->getWorldTime()) {
		_frame.count = TIMEMANAGER->getWorldTime();
		if (_frame.currentFrameX >= _frame.maxFrameX - 1) {
			if (_status == FumeshroomStatus::SHOT) {
				_status = FumeshroomStatus::WAIT;
				_alreadyShot = false;
			}
			_frame.currentFrameX = 0;
		}
		else _frame.currentFrameX += 1;
	}
}
