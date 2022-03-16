#include "Stdafx.h"
#include "Plant.h"

HRESULT Plant::init(PlantType type, POINT location) {
	_type = type;
	_location = location;
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
