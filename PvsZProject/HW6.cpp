#include "Stdafx.h"
#include "HW6.h"

HRESULT HW6::init(void) {
	GameNode::init();
	return S_OK;
}

void HW6::release(void) {
}

void HW6::update(void) {
	GameNode::update();
}

void HW6::render() {
	HDC memDC = this->getBackBuffer()->getMemDC();
	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	this->getBackBuffer()->render(getMemDC(), 0, 0);
}