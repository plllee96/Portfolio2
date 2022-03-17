#include "Stdafx.h"
#include "Peashooter.h"

HRESULT Peashooter::init(PlantType type, POINT location) {
	Plant::init(type, location);
	_image = IMAGEMANAGER->addFrameImage("Peashooter", "Resources/Images/Plants/Peashooter.bmp", 432, 128, 8, 2, true, RGB(255, 0, 255));
	_rc = RectMake(startX + _location.x * tileWidth, startY + _location.y * firstMapTileHeight, tileWidth, firstMapTileHeight);

	_status = PeashooterStatus::WAIT;

	return S_OK;
}

void Peashooter::release(void) {
	Plant::release();
}

void Peashooter::update(void) {
	Plant::update();
	setFrame();
	updateFrame();
}

void Peashooter::render(void) {
	_image->frameRender(getMemDC(), _rc.left, _rc.top, _frame.currentFrameX, _frame.currentFrameY);
}

void Peashooter::act() {

}

void Peashooter::setFrame() {
	switch (_status) {
		case PeashooterStatus::WAIT: {
			_frame.maxFrameX = 8;
			_frame.coolTime = 0.5f;
			_frame.currentFrameY = 0;
		} break;
		case PeashooterStatus::SHOT: {
			_frame.maxFrameX = 3;
			_frame.coolTime = 0.1f;
			_frame.currentFrameY = 1;
		} break;
	}
}

void Peashooter::updateFrame() {
	if (_frame.count + _frame.coolTime < TIMEMANAGER->getWorldTime()) {
		_frame.count = TIMEMANAGER->getWorldTime();
		if (_frame.currentFrameX >= _frame.maxFrameX - 1) _frame.currentFrameX = 0;
		else _frame.currentFrameX+= 1;
	}
}
