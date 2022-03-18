#include "Stdafx.h"
#include "PlantManager.h"

HRESULT PlantManager::init(void) {
	return S_OK;
}

void PlantManager::release(void) {
}

void PlantManager::update(void) {
	_viPlant = _vPlant.begin();
	for (; _viPlant != _vPlant.end(); ++_viPlant) {
		(*_viPlant)->update();
	}
}

void PlantManager::render(void) {
	_viPlant = _vPlant.begin();
	for (; _viPlant != _vPlant.end(); ++_viPlant) {
		(*_viPlant)->render();
	}
}

void PlantManager::addPlant(PlantType type, POINT location) {
	Plant* temp;
	switch (type) {
		case PlantType::PEASHOOTER: temp = new Peashooter; break;
		case PlantType::SUNFLOWER: temp = new Sunflower; break;
		default: temp = new Plant;
	}
	temp->init(type, location);
	_vPlant.push_back(temp);

}

void PlantManager::removePlant(int index) {
	_vPlant[index]->release();
	_vPlant.erase(_vPlant.begin() + index);
}

void PlantManager::removePlant(viPlant iter) {
	(*iter)->release();
	_vPlant.erase(iter);
}
