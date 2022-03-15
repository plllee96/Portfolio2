#include "Stdafx.h"
#include "Sun.h"

HRESULT Sun::init(SunType type) {
	_image = IMAGEMANAGER->addFrameImage("Sun", "Resources/Images/Objects/Sun.bmp", 106, 52, 2, 1, true, RGB(255, 0, 255));
	_type = type;
	if (type == SunType::FALL) {
		_x = RND->getFromIntTo(64, 526);
		_y = -_image->getFrameHeight();
		_targetY = RND->getFromIntTo(92, 336);
	}
	_timer = 0.0f;
	_frame = 0;
	_frameTimer = TIMEMANAGER->getWorldTime();
	return S_OK;
}

HRESULT Sun::init(SunType type, float x, float y) {
	_image = IMAGEMANAGER->addFrameImage("Sun", "Resources/Images/Objects/Sun.bmp", 106, 52, 2, 1, true, RGB(255, 0, 255));
	_type = type;
	if (type == SunType::GENERATE) {
		
	}
	_timer = 0.0f;
	_frame = 0;
	_frameTimer = TIMEMANAGER->getWorldTime();
	return S_OK;
}

void Sun::release(void) {
	
}

void Sun::update(void) {
	switch (_type) {
		case SunType::FALL: {
			if (_timer == 0.0f) {
				_y += 0.7f;
				if (_y >= _targetY) _timer = TIMEMANAGER->getWorldTime();
			}
		} break;
		case SunType::GENERATE: {

		} break;
		case SunType::GAIN: {
			if (_x > uiX) 	_x -= (_x - uiX) * 0.05f;
			if (_y > uiY) 	_y -= (_y - uiY) * 0.05f;
		} break;
	}
	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
	updateFrame();
}

void Sun::render(void) {
	//Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
	_image->frameRender(getMemDC(), _rc.left, _rc.top, _frame, 0);
}

void Sun::updateFrame(void) {
	if (_frameTimer + sunFrameDelay < TIMEMANAGER->getWorldTime()) {
		if (_frame == 0) _frame = 1;
		else if (_frame == 1) _frame = 0;
		_frameTimer = TIMEMANAGER->getWorldTime();
	}
}

bool Sun::isOverTime() {
	if (_timer == 0) return false;
	else if (_type == SunType::GAIN) return false;
	else if (_timer + sunCooltime < TIMEMANAGER->getWorldTime()) return true;
	else return false;
}

bool Sun::isCompleteObtained() {
	if (_type == SunType::GAIN) {
		if (MY_UTIL::getDistance(uiX, uiY, _x, _y) < 10.0f) return true;
		else return false;
	}
	else return false;
}
