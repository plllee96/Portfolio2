#include "Stdafx.h"
#include "ObjectEffect.h"

HRESULT ObjectEffect::init(void) {
	return S_OK;
}

HRESULT ObjectEffect::init(const char * imageName, int x, int y) {
	_image = IMAGEMANAGER->findImage(imageName);
	_x = x;
	_y = y;
	_isActive = true;
	_targetY = _y + RND->getFromFloatTo(30.0f, 50.0f);
	_xspeed = RND->getFromFloatTo(0.0f, 1.5f);
	_gravity = RND->getFromFloatTo(0.5f, 1.5f);
	_timer = TIMEMANAGER->getWorldTime();
	return S_OK;
}

void ObjectEffect::release(void) {
}

void ObjectEffect::update(void) {
	if (_y <= _targetY) {
		_y -= _gravity;
		_x += _xspeed;
		_gravity -= 0.1f;
	}

	if (_timer + maintainTime < TIMEMANAGER->getWorldTime()) _isActive = false;
}

void ObjectEffect::render(void) {
	_image->render(getMemDC(), _x, _y);
}
