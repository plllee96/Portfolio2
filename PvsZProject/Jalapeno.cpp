#include "Stdafx.h"
#include "Jalapeno.h"

HRESULT Jalapeno::init(PlantType type, POINT location) {
	Plant::init(type, location);
	_image = IMAGEMANAGER->addFrameImage("Jalapeno", "Resources/Images/Plants/Jalapeno.bmp", 378, 74, 7, 1, true, RGB(255, 0, 255));
	_rc = _recognizeRc = RectMake(startX + _location.x * tileWidth, startY + _location.y * _tileHeight - 20, tileWidth, _tileHeight);

	_bulletType = BulletType::JALAPENO_EXPLODE;

	_fireX = _rc.left;
	_fireY = _rc.top;

	_frame.maxFrameX = 6;
	_frame.coolTime = 0.14f;
	_frame.currentFrameY = 0;
	return S_OK;
}

void Jalapeno::release(void) {
	Plant::release();
}

void Jalapeno::update(void) {
	if (_fire) _active = false;
	updateFrame();
}

void Jalapeno::render(void) {
	_image->frameRender(getMemDC(), _rc.left, _rc.top, _frame.currentFrameX, _frame.currentFrameY);
}

void Jalapeno::updateFrame() {
	if (_frame.count + _frame.coolTime < TIMEMANAGER->getWorldTime()) {
		_frame.count = TIMEMANAGER->getWorldTime();
		if (_frame.currentFrameX > _frame.maxFrameX) {
			_fire = true;
		}
		_frame.currentFrameX += 1;
	}
}
