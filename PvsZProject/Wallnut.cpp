#include "Stdafx.h"
#include "Wallnut.h"

HRESULT Wallnut::init(PlantType type, POINT location) {
	Plant::init(type, location);
	_image = IMAGEMANAGER->addFrameImage("Wallnut", "Resources/Images/Plants/Wallnut.bmp", 270, 192, 5, 3, true, RGB(255, 0, 255));
	_rc = _recognizeRc = RectMake(startX + _location.x * tileWidth, startY + _location.y * firstMapTileHeight, tileWidth, firstMapTileHeight);

	_hp = 72.0f;

	_frame.maxFrameX = 5;
	_frame.coolTime = 0.5f;
	_frame.currentFrameY = 0;
	return S_OK;
}

void Wallnut::release(void) {
	Plant::release();
}

void Wallnut::update(void) {
	Plant::update();
	act();
	setFrame();
	updateFrame();
}

void Wallnut::render(void) {
	Plant::render();
	_image->frameRender(getMemDC(), _rc.left, _rc.top, _frame.currentFrameX, _frame.currentFrameY);
}

void Wallnut::act() {
}

void Wallnut::setFrame() {
	if (_hp > 48.0f) _frame.currentFrameY = 0;
	else if (_hp > 24.0f) _frame.currentFrameY = 1;
	else _frame.currentFrameY = 2;
}

void Wallnut::updateFrame() {
	if (_frame.count + _frame.coolTime < TIMEMANAGER->getWorldTime()) {
		_frame.count = TIMEMANAGER->getWorldTime();

		if (_frame.currentFrameX >= _frame.maxFrameX - 1) {
			_frame.currentFrameX = 0;
		}
		else _frame.currentFrameX += 1;
	}
}
