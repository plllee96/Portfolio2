#include "Stdafx.h"
#include "NumberImage.h"

HRESULT NumberImage::init(float* x, float* y) {
	_numberImage = IMAGEMANAGER->addFrameImage("Number", "Resources/Images/Objects/Number.bmp", 140, 18, 10, 1, true, RGB(255, 0, 255));
	_x = x;
	_y = y;
	return S_OK;
}

void NumberImage::release(void) {
}

void NumberImage::update(void) {
	// ! Do Nothing
}

void NumberImage::render(void) {
	_numberImage->frameRender(getMemDC(), *_x, *_y, 0, 0);
}

void NumberImage::render(int num) {
	if (num > 9999) {
		_numberImage->frameRender(getMemDC(), *_x - 15, *_y, 9, 0);
		_numberImage->frameRender(getMemDC(), *_x - 5, *_y, 9, 0);
		_numberImage->frameRender(getMemDC(), *_x + 5, *_y, 9, 0);
		_numberImage->frameRender(getMemDC(), *_x + 15, *_y, 9, 0);
	}
	else if (num > 999) {
		int thousandNumber = num / 1000;
		int hundredNumber = (num % 1000) / 100;
		int tenNumber = (num % 100) / 10;
		int firstNumber = num % 10;
		_numberImage->frameRender(getMemDC(), *_x - 15, *_y, thousandNumber, 0);
		_numberImage->frameRender(getMemDC(), *_x - 5, *_y, hundredNumber, 0);
		_numberImage->frameRender(getMemDC(), *_x + 5, *_y, tenNumber, 0);
		_numberImage->frameRender(getMemDC(), *_x + 15, *_y, firstNumber, 0);
	}
	else if (num > 99) {
		int hundredNumber = (num % 1000) / 100;
		int tenNumber = (num % 100) / 10;
		int firstNumber = num % 10;
		_numberImage->frameRender(getMemDC(), *_x - 10, *_y, hundredNumber, 0);
		_numberImage->frameRender(getMemDC(), *_x, *_y, tenNumber, 0);
		_numberImage->frameRender(getMemDC(), *_x + 10, *_y, firstNumber, 0);
	}
	else if (num > 9) {
		_numberImage->frameRender(getMemDC(), *_x - 5, *_y, num / 10, 0);
		_numberImage->frameRender(getMemDC(), *_x + 5, *_y, num % 10, 0);
	}
	else if (num > 0) {
		_numberImage->frameRender(getMemDC(), *_x, *_y, num, 0);
	}
	else {
		_numberImage->frameRender(getMemDC(), *_x, *_y, 0, 0);
	}
}
