#include "Stdafx.h"
#include "PlantManager.h"

HRESULT PlantManager::init(void) {
	return S_OK;
}

void PlantManager::release(void) {
}

void PlantManager::update(void) {
}

void PlantManager::render(void) {
}

void PlantManager::addPlant(PlantType type, POINT location) {
	Plant* temp = new Plant;
	temp->init(type, location);
}
