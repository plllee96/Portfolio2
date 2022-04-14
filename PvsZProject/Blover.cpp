#include "Stdafx.h"
#include "Blover.h"

HRESULT Blover::init(PlantType type, POINT location) {
	Plant::init(type, location);
	_image = IMAGEMANAGER->addFrameImage("Blover", "Resources/Images/Plants/Blover.bmp", 1224, 228, 9, 2, true, RGB(255, 0, 255));
	_rc = _recognizeRc = RectMake(startX + _location.x * tileWidth - 25, startY + _location.y * _tileHeight, tileWidth, _tileHeight);

	_status = BloverStatus::WAIT;
	_blowCount = 0;
	_blow = false;

	_frame.maxFrameX = 9;
	_frame.coolTime = 0.1f;
	_frame.currentFrameY = 0;

	return S_OK;
}

void Blover::release(void) {
	Plant::release();
}

void Blover::update(void) {
	if (_blowCount > 6) _active = false;
	updateFrame();
}

void Blover::render(void) {
	_image->frameRender(getMemDC(), _rc.left, _rc.top - 50, _frame.currentFrameX, _frame.currentFrameY);
}

void Blover::updateFrame() {
	if (_frame.count + _frame.coolTime < TIMEMANAGER->getWorldTime()) {
		_frame.count = TIMEMANAGER->getWorldTime();
		_frame.currentFrameX += 1;

		if (_frame.currentFrameX > _frame.maxFrameX) {
			if (_status == BloverStatus::WAIT) {
				_status = BloverStatus::BLOW;
				_blow = true;
				_frame.currentFrameX = 0;
				_frame.maxFrameX = 2;
				_frame.coolTime = 0.05f;
				_frame.currentFrameY = 1;
			}
			else if (_status == BloverStatus::BLOW) {
				_frame.currentFrameX = 0;
				_blowCount++;
			}
		}
	}
}
