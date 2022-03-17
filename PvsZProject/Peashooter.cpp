#include "Stdafx.h"
#include "Peashooter.h"

HRESULT Peashooter::init(PlantType type, POINT location) {
	Plant::init(type, location);
	return S_OK;
}

void Peashooter::release(void) {
	Plant::release();
}

void Peashooter::update(void) {
	Plant::update();
}

void Peashooter::render(void) {
	Plant::render();
}

void Peashooter::act() {
}
