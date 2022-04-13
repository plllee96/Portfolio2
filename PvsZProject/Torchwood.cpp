#include "Stdafx.h"
#include "Torchwood.h"

HRESULT Torchwood::init(PlantType type, POINT location) {
	Plant::init(type, location);
	_image = IMAGEMANAGER->addFrameImage("Torchwood", "Resources/Images/Plants/Torchwood.bmp", 448, 76, 8, 1, true, RGB(255, 0, 255));
	_rc = _recognizeRc = RectMake(startX + _location.x * tileWidth, startY + _location.y * _tileHeight, tileWidth, _tileHeight);

	_hp = 5.0;

	_frame.maxFrameX = 5;
	_frame.coolTime = 0.5f;
	_frame.currentFrameY = 0;
	return S_OK;
}

void Torchwood::release(void) {
	Plant::release();
}

void Torchwood::update(void) {
	Plant::update();
	act();
	updateFrame();
}

void Torchwood::render(void) {
	Plant::render();
	_image->frameRender(getMemDC(), _rc.left, _rc.top - 10, _frame.currentFrameX, _frame.currentFrameY);
}

void Torchwood::act() {

}

void Torchwood::updateFrame() {
	if (_frame.count + _frame.coolTime < TIMEMANAGER->getWorldTime()) {
		_frame.count = TIMEMANAGER->getWorldTime();

		if (_frame.currentFrameX >= _frame.maxFrameX - 1) {
			_frame.currentFrameX = 0;
		}
		else _frame.currentFrameX += 1;
	}
}
