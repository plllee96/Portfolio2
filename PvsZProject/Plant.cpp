#include "Stdafx.h"
#include "Plant.h"

HRESULT Plant::init(PlantType type, POINT location) {
	_type = type;
	_location = location;

	_frame.maxFrameX = 1;
	_frame.currentFrameX = 0;
	_frame.currentFrameY = 0;
	_frame.count = TIMEMANAGER->getWorldTime();
	_frame.coolTime = 0.5f;

	return S_OK;
}

void Plant::release(void) {
}

void Plant::update(void) {
	act();
}

void Plant::render(void) {
}

void Plant::act() {
}
