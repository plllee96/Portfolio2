#include "Stdafx.h"
#include "InvisibleRect.h"

HRESULT InvisibleRect::init(BulletType type, int x, int y, int line) {
	Bullet::init(type, x, y, line);
	_availableTime = TIMEMANAGER->getWorldTime();
	_rc = RectMake(x, y, 80, 30);
	_damage = 99999.0f;
	cout << "InvisibleRect::init" << endl;
	return S_OK;
}

void InvisibleRect::release(void) {
	Bullet::release();
}

void InvisibleRect::update(void) {
	if (_availableTime == TIMEMANAGER->getWorldTime()) {
		_hitActive = true;
	}
	else _hitActive = false;
}

void InvisibleRect::render(void) {
	Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
}

void InvisibleRect::collideObject(ObserveData obData) {
	if(*obData.line == _line) _active = false;
}

void InvisibleRect::recognizeObject(ObserveData observer) {
}
