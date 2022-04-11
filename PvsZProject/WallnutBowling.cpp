#include "Stdafx.h"
#include "WallnutBowling.h"

HRESULT WallnutBowling::init(PlantType type, POINT location) {
	Plant::init(type, location);
	_image = IMAGEMANAGER->addFrameImage("WallnutBowling", "Resources/Images/Plants/WallnutBowling.bmp", 480, 60, 8, 1, true, RGB(255, 0, 255));
	_bowlingX = startX + _location.x * tileWidth;
	_bowlingY = startY + _location.y * _tileHeight;
	_rc = _recognizeRc = RectMake(_bowlingX, _bowlingY, tileWidth, _tileHeight);
	
	_frame.maxFrameX = 8;
	_frame.coolTime = 0.08f;
	_frame.currentFrameY = 0;

	_historyLine = location.y;

	_bowlingCount = TIMEMANAGER->getWorldTime();
	_bowlingCooltime = 0.45f;

	_moveTo = 0;
	return S_OK;
}

void WallnutBowling::release(void) {
	Plant::release();
}

void WallnutBowling::update(void) {
	Plant::update();
	updateFrame();

	if (_bowlingY > 0 && _bowlingY < 114) _line = 0;
	else if (_bowlingY >= 114 && _bowlingY < 177) _line = 1;
	else if (_bowlingY >= 177 && _bowlingY < 240) _line = 2;
	else if (_bowlingY >= 240 && _bowlingY < 303) _line = 3;
	else if (_bowlingY >= 303) _line = 4;
	if (_historyLine != _line) {
		_hitActive = true;
		_historyLine = _line;
	}

	if(_bowlingX > WINSIZE_X) _active = false;

	if (_bowlingY < 50) _moveTo = 1;
	else if (_bowlingY > 310) _moveTo = -1;
	

	_bowlingX += 2.0f;
	_bowlingY += 2 * _moveTo;
	_rc = _recognizeRc = RectMake(_bowlingX, _bowlingY, tileWidth, _tileHeight);
}

void WallnutBowling::render(void) {
	_image->frameRender(getMemDC(), _rc.left, _rc.top, _frame.currentFrameX, _frame.currentFrameY);
}

void WallnutBowling::recognizeObject(ObserveData observer) {
	if (_hitActive) {
		if (_moveTo == 0) {
			if (_line == 0) _moveTo = 1;
			else if (_line == 4) _moveTo = -1;
			else _moveTo = 2 * RND->getInt(2) - 1;
		}
		else if (_moveTo == 1) _moveTo = -1;
		else if (_moveTo == -1) _moveTo = 1;
	}
	_hitActive = false;
}

void WallnutBowling::updateFrame() {
	if (_frame.count + _frame.coolTime < TIMEMANAGER->getWorldTime()) {
		_frame.count = TIMEMANAGER->getWorldTime();

		if (_frame.currentFrameX >= _frame.maxFrameX - 1) {
			_frame.currentFrameX = 0;
		}
		else _frame.currentFrameX += 1;
	}
}
