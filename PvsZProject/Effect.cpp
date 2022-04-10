#include "Stdafx.h"
#include "Effect.h"

HRESULT Effect::init(void) {
	return S_OK;
}

HRESULT Effect::init(const char* imageName, float delay, int x, int y) {
	_image = IMAGEMANAGER->findImage(imageName);
	_count = TIMEMANAGER->getWorldTime();
	_delay = delay;
	_x = x;
	_y = y;
	_isActive = true;

	return S_OK;
}


void Effect::release(void) {
}

void Effect::update(void) {
	updateFrame();
}

void Effect::render(void) {
	_image->frameRender(getMemDC(), _x, _y, _currentFrameX, _currentFrameY);
}

void Effect::updateFrame() {
	if (_count + _delay < TIMEMANAGER->getWorldTime()) {
		_count = TIMEMANAGER->getWorldTime();
		_currentFrameX++;
		if (_currentFrameX > _image->getMaxFrameX()) {
			_isActive = false;
			SOUNDMANAGER->stop("Hit");
		}
	}
}


Effect::Effect(void) {
	_currentFrameX = 0;
	_currentFrameY = 0;
	_x = 0;
	_y = 0;
	_count = 0;
	_delay = 0;
	_isActive = false;
}

Effect::~Effect(void) {
}
