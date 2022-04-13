#include "Stdafx.h"
#include "Plantern.h"

HRESULT Plantern::init(PlantType type, POINT location) {
	Plant::init(type, location);
	_image = IMAGEMANAGER->addFrameImage("Plantern", "Resources/Images/Plants/Plantern.bmp", 264, 72, 4, 1, true, RGB(255, 0, 255));
	_rc = _recognizeRc = RectMake(startX + _location.x * tileWidth, startY + _location.y * _tileHeight, tileWidth, _tileHeight);

	_hp = 5.0;

	_frame.maxFrameX = 5;
	_frame.coolTime = 0.5f;
	_frame.currentFrameY = 0;
	return S_OK;
}

void Plantern::release(void) {
	Plant::release();
}

void Plantern::update(void) {
	Plant::update();
	act();
	updateFrame();
}

void Plantern::render(void) {
	Plant::render();
	_image->frameRender(getMemDC(), _rc.left, _rc.top - 5, _frame.currentFrameX, _frame.currentFrameY);
}

void Plantern::act() {

}

void Plantern::updateFrame() {
	if (_frame.count + _frame.coolTime < TIMEMANAGER->getWorldTime()) {
		_frame.count = TIMEMANAGER->getWorldTime();

		if (_frame.currentFrameX >= _frame.maxFrameX - 1) {
			_frame.currentFrameX = 0;
		}
		else _frame.currentFrameX += 1;
	}
}
