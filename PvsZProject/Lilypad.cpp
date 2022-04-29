#include "Stdafx.h"
#include "Lilypad.h"

HRESULT Lilypad::init(PlantType type, POINT location) {
	Plant::init(type, location);
	_image = IMAGEMANAGER->addImage("Lilypad", "Resources/Images/Plants/Lilypad.bmp", 48, 38, true, RGB(255, 0, 255));
	_rc = _recognizeRc = RectMake(startX + _location.x * tileWidth + 4, startY + _location.y * _tileHeight + 30, tileWidth, _tileHeight);

	_hp = 72.0f;

	_frame.maxFrameX = 5;
	_frame.coolTime = 0.1f;
	_frame.currentFrameY = 0;
	return S_OK;
}

void Lilypad::release(void) {
	Plant::release();
}

void Lilypad::update(void) {
	Plant::update();
	act();
}

void Lilypad::render(void) {
	_image->render(getMemDC(), _rc.left, _rc.top);
}
