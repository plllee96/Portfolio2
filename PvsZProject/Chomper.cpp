#include "Stdafx.h"
#include "Chomper.h"

HRESULT Chomper::init(PlantType type, POINT location) {
	Plant::init(type, location);
	_image = IMAGEMANAGER->addFrameImage("Chomper", "Resources/Images/Plants/Chomper.bmp", 990, 220, 9, 2, true, RGB(255, 0, 255));
	_rc = RectMake(startX + _location.x * tileWidth, startY + _location.y * _tileHeight, tileWidth, _tileHeight);
	_recognizeRc = RectMake(startX + _location.x * tileWidth, startY + _location.y * _tileHeight, tileWidth*2, _tileHeight);
	_status = ChomperStatus::WAIT;
	_bulletType = BulletType::INVISIBLE_RECT;

	_attackCoolTime = 20.0f;
	_alreadyAttack = false;

	fixFireX = 45;
	fixFireY = 5;

	_fireX = _rc.left + fixFireX;
	_fireY = _rc.top + fixFireY;

	return S_OK;
}

void Chomper::release(void) {
	Plant::release();
}

void Chomper::update(void) {
	Plant::update();
	if (_alreadyAttack) _fire = false;
	setFrame();
	updateFrame();
}

void Chomper::render(void) {
	_image->frameRender(getMemDC(), _rc.left - 5, _rc.top - 50, _frame.currentFrameX, _frame.currentFrameY);
}

void Chomper::recognizeObject(ObserveData observer) {
	if (_status == ChomperStatus::WAIT && _line == *observer.line) {
		_status = ChomperStatus::ATTACK;
		_attackCount = TIMEMANAGER->getWorldTime();
		_frame.currentFrameX = 0;
	}
}

void Chomper::setFrame() {
	switch (_status) {
		case ChomperStatus::WAIT: {
			_frame.maxFrameX = 9;
			_frame.coolTime = 0.1f;
			_frame.currentFrameY = 0;
		} break;
		case ChomperStatus::ATTACK: {
			_frame.maxFrameX = 9;
			_frame.coolTime = 0.1f;
			_frame.currentFrameY = 1;
		} break;
	}
}

void Chomper::updateFrame() {
	if (_frame.count + _frame.coolTime < TIMEMANAGER->getWorldTime()) {
		_frame.count = TIMEMANAGER->getWorldTime();
		if (_frame.currentFrameX >= _frame.maxFrameX - 1) {
			if (_status == ChomperStatus::WAIT) {
				_frame.currentFrameX = 0;
			}
		}
		else {
			if (_status == ChomperStatus::ATTACK && _frame.currentFrameX == 2 && !_alreadyAttack) {
				_attackCount = TIMEMANAGER->getWorldTime();
				_fire = true;
				_alreadyAttack = true;
			}
			else _fire = false;
			_frame.currentFrameX += 1;
		}
	}

	if (_status == ChomperStatus::ATTACK && _attackCount + _attackCoolTime < TIMEMANAGER->getWorldTime()) {
		_status = ChomperStatus::WAIT;
		_alreadyAttack = false;
	}
}
