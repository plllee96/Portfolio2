#include "Stdafx.h"
#include "Scaredyshroom.h"

HRESULT Scaredyshroom::init(PlantType type, POINT location) {
	Plant::init(type, location);
	_image = IMAGEMANAGER->addFrameImage("ScaredyShroom", "Resources/Images/Plants/ScaredyShroom.bmp", 232, 198, 4, 3, true, RGB(255, 0, 255));
	_rc = RectMake(startX + _location.x * tileWidth - 10, startY + _location.y * _tileHeight - 5, tileWidth, _tileHeight);
	_recognizeRc = RectMake(startX + _location.x * tileWidth + (tileWidth / 2), startY + _location.y * _tileHeight + 10, WINSIZE_X, _tileHeight - 20);
	_scaredRect = RectMake(startX + _location.x * tileWidth + (tileWidth / 2), startY + _location.y * _tileHeight + 10, tileWidth * 1.2 , _tileHeight - 20);

	
	_status = ScaredyshroomStatus::WAIT;
	_bulletType = BulletType::MUSHROOM_BULLET;

	fixFireX = 25;
	fixFireY = 15;

	_shotCount = TIMEMANAGER->getWorldTime();
	_shotCooltime = 1.5f;
	_alreadyShot = false;

	_fireX = _rc.left + fixFireX;
	_fireY = _rc.top + fixFireY;

	return S_OK;
}

void Scaredyshroom::release(void) {
	Plant::release();
}

void Scaredyshroom::update(void) {
	Plant::update();
	setFrame();
	updateFrame();
}

void Scaredyshroom::render(void) {
	_image->frameRender(getMemDC(), _rc.left, _rc.top, _frame.currentFrameX, _frame.currentFrameY);
}

void Scaredyshroom::act() {
	if (_status == ScaredyshroomStatus::SHOT) {
		if (_frame.currentFrameX == 1 && !_alreadyShot) {
			_alreadyShot = true;
			fire(true);
		}
		else fire(false);
	}
}

void Scaredyshroom::fire(bool fire) {
	_fire = fire;
}

void Scaredyshroom::recognizeObject(ObserveData observer) {
	//Scraed 범위 설정
	RECT temp;
	if (IntersectRect(&temp, &_scaredRect, observer.rc)) {
		_status = ScaredyshroomStatus::SCARED;
		_frame.currentFrameX = 0;
	}
	else if (_shotCooltime + _shotCount < TIMEMANAGER->getWorldTime()) {
		_status = ScaredyshroomStatus::SHOT;
		_frame.currentFrameX = 0;
		_shotCount = TIMEMANAGER->getWorldTime();
	}
}
void Scaredyshroom::setFrame() {
	switch (_status) {
		case ScaredyshroomStatus::WAIT: {
			_frame.maxFrameX = 4;
			_frame.coolTime = 0.5f;
			_frame.currentFrameY = 0;
		} break;
		case ScaredyshroomStatus::SHOT: {
			_frame.maxFrameX = 2;
			_frame.coolTime = 0.3f;
			_frame.currentFrameY = 1;
		} break;
		case ScaredyshroomStatus::SCARED: {
			_frame.maxFrameX = 2;
			_frame.coolTime = 0.5f;
			_frame.currentFrameY = 2;
		} break;
	}
}

void Scaredyshroom::updateFrame() {
	if (_frame.count + _frame.coolTime < TIMEMANAGER->getWorldTime()) {
		_frame.count = TIMEMANAGER->getWorldTime();
		if (_frame.currentFrameX >= _frame.maxFrameX - 1) {
			if (_status == ScaredyshroomStatus::SHOT || _status == ScaredyshroomStatus::SCARED) {
				_status = ScaredyshroomStatus::WAIT;
				_alreadyShot = false;
			}
			_frame.currentFrameX = 0;
		}
		else _frame.currentFrameX += 1;
	}
}
