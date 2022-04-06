#include "Stdafx.h"
#include "ArmEffect.h"

HRESULT ArmEffect::init(void) {
	return S_OK;
}

HRESULT ArmEffect::init(const char * imageName, int x, int y) {
	_image = IMAGEMANAGER->findImage(imageName);
	 _x = x;
	_firstY = _y = y;
	_isActive = true;

	return S_OK;
}

void ArmEffect::release(void) {
}

void ArmEffect::update(void) {
	_y++;
	if (_y > _firstY + 27) _isActive = false;
}

void ArmEffect::render(void) {
	_image->render(getMemDC(), _x, _y);
}
