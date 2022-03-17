#include "Stdafx.h"
#include "Sunflower.h"

HRESULT Sunflower::init(PlantType type, POINT location) {
	Plant::init(type, location);
	return S_OK;
}

void Sunflower::release(void) {
	Plant::release();
}

void Sunflower::update(void) {
	Plant::update();
}

void Sunflower::render(void) {
	Plant::render();
}

void Sunflower::act() {
}
