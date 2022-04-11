#include "Stdafx.h"
#include "ExplodeBowling.h"

HRESULT ExplodeBowling::init(PlantType type, POINT location) {
	Plant::init(type, location);
	_image = IMAGEMANAGER->addFrameImage("ExplodeBowling", "Resources/Images/Plants/ExplodeBowling.bmp", 480, 60, 8, 1, true, RGB(255, 0, 255));
	_bowlingX = startX + _location.x * tileWidth;
	_rc = _recognizeRc = RectMake(_bowlingX, startY + _location.y * _tileHeight, tileWidth, _tileHeight);

	_bulletType = BulletType::CHERRY_EXPLODE;

	_frame.maxFrameX = 8;
	_frame.coolTime = 0.08f;
	_frame.currentFrameY = 0;

	return S_OK;

}

void ExplodeBowling::release(void) {
	Plant::release();
}

void ExplodeBowling::update(void) {
	Plant::update();
	if (_fire) _active = false;
	updateFrame();

	if (_bowlingX > WINSIZE_X) _active = false;

	_bowlingX += 2.0f;
	_rc = _recognizeRc = RectMake(_bowlingX, startY + _location.y * _tileHeight, tileWidth, _tileHeight);
}

void ExplodeBowling::render(void) {
	_image->frameRender(getMemDC(), _rc.left, _rc.top, _frame.currentFrameX, _frame.currentFrameY);
}

void ExplodeBowling::recognizeObject(ObserveData observer) {
	_fire = true;
}

void ExplodeBowling::updateFrame() {
	if (_frame.count + _frame.coolTime < TIMEMANAGER->getWorldTime()) {
		_frame.count = TIMEMANAGER->getWorldTime();

		if (_frame.currentFrameX >= _frame.maxFrameX - 1) {
			_frame.currentFrameX = 0;
		}
		else _frame.currentFrameX += 1;
	}
}
