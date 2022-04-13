#include "Stdafx.h"
#include "PlantManager.h"

HRESULT PlantManager::init(void) {
	return S_OK;
}

void PlantManager::release(void) {
	_viPlant = _vPlant.begin();
	for (; _viPlant != _vPlant.end(); ++_viPlant) {
		int temp = (*_viPlant)->getLocation().x + _tile->getColumn() * (*_viPlant)->getLocation().y;
		_tile->setPlant(temp, false);
		(*_viPlant)->release();
	}
	_vPlant.clear();
}

void PlantManager::update(void) {
	_viPlant = _vPlant.begin();
	for (; _viPlant != _vPlant.end(); ++_viPlant) {
		(*_viPlant)->update();
		if (!(*_viPlant)->isActive()) {
			if ((*_viPlant)->getType() == PlantType::GRAVEBUSTER) {
				removeObstacle(_viPlant);
			}
			removePlant(_viPlant);
			break;
		}
	}
}

void PlantManager::render(void) {
	int row;
	if (_stageNum == 0 || _stageNum == 1) row = 5;
	else row = 6;

	for (int i = 0; i < row; i++) {
		_viPlant = _vPlant.begin();
		for (; _viPlant != _vPlant.end(); ++_viPlant) {
			if ((*_viPlant)->getLine() == i) (*_viPlant)->render();
		}
	}
}

void PlantManager::addPlant(PlantType type, POINT location) {
	Plant* temp;
	switch (type) {
		case PlantType::PEASHOOTER: temp = new Peashooter; break;
		case PlantType::SUNFLOWER: temp = new Sunflower; break;
		case PlantType::WALLNUT: temp = new Wallnut; break;
		case PlantType::CHERRYBOMB: temp = new CherryBomb; break;
		case PlantType::POTATOMINE: temp = new PotatoMine; break;
		case PlantType::CHOMPER: temp = new Chomper; break;

		case PlantType::PUFFSHROOM: temp = new Puffshroom; break;
		case PlantType::SUNSHROOM: temp = new Sunshroom; break;
		case PlantType::SCAREDYSHROOM: temp = new Scaredyshroom; break;
		case PlantType::FUMESHROOM: temp = new FumeShroom; break;
		case PlantType::GRAVEBUSTER: temp = new Gravebuster; break;

		case PlantType::LILYPAD: temp = new Lilypad; break;
		case PlantType::CABBAGEPULT: temp = new Cabbagepult; break;
		case PlantType::CACTUS: temp = new Cactus; break;
		case PlantType::JALAPENO: temp = new Jalapeno; break;
		case PlantType::THREEPEATER: temp = new Threepeater; break;		

		case PlantType::TWINSUNFLOWER: temp = new TwinSunflower; break;
		case PlantType::WALLNUTBOWLING: temp = new WallnutBowling; break;
		case PlantType::EXPLODEBOWLING: temp = new ExplodeBowling; break;

		case PlantType::PLANTERN: temp = new Plantern; break;
		case PlantType::BLOVER: temp = new Blover; break;
		case PlantType::SEASHROOM: temp = new Seashroom; break;
		case PlantType::SQUASH: temp = new Squash; break;
		case PlantType::TORCHWOOD: temp = new Torchwood; break;

		default: temp = new Plant;
	}
	temp->setTileHeight(_currentTile);
	temp->init(type, location);
	_vPlant.push_back(temp);

}

void PlantManager::removePlant(int index) {
	_vPlant[index]->release();
	_vPlant.erase(_vPlant.begin() + index);
}

void PlantManager::removePlant(viPlant iter) {
	int temp = (*iter)->getLocation().x + _tile->getColumn() * (*iter)->getLocation().y;
	_tile->setPlant(temp, false);
	(*iter)->release();
	_vPlant.erase(iter);
}

void PlantManager::removeObstacle(viPlant iter) {
	int temp = (*iter)->getLocation().x + _tile->getColumn() * (*iter)->getLocation().y;
	_tile->setObstacle(temp, false);
}

generateTypeContainer PlantManager::isGeneratePlant() {
	generateTypeContainer tempContainer;
	_viPlant = _vPlant.begin();
	for (; _viPlant != _vPlant.end(); ++_viPlant) {
		if ((*_viPlant)->getType() == PlantType::SUNFLOWER) {
			Sunflower* temp = static_cast<Sunflower*>(*_viPlant);
			if (temp->isGenerate()) {
				tempContainer.isGenerate = true;
				tempContainer.x = temp->getRect().left;
				tempContainer.y = temp->getRect().top;
				tempContainer.isSmallSun = false;
				tempContainer.isTwin = false;
				temp->setGenerate(false);
				return tempContainer;
			}
			else continue;
		}
		else if ((*_viPlant)->getType() == PlantType::SUNSHROOM) {
			Sunshroom* temp = static_cast<Sunshroom*>(*_viPlant);
			if (temp->isGenerate()) {
				tempContainer.isGenerate = true;
				tempContainer.x = temp->getRect().left;
				tempContainer.y = temp->getRect().top;
				if (temp->isGrow()) tempContainer.isSmallSun = false;
				else tempContainer.isSmallSun = true;
				tempContainer.isTwin = false;
				temp->setGenerate(false);
				return tempContainer;
			}
			else continue;
		}
		else if ((*_viPlant)->getType() == PlantType::TWINSUNFLOWER) {
			Sunflower* temp = static_cast<Sunflower*>(*_viPlant);
			if (temp->isGenerate()) {
				tempContainer.isGenerate = true;
				tempContainer.x = temp->getRect().left;
				tempContainer.y = temp->getRect().top;
				tempContainer.isSmallSun = false;
				tempContainer.isTwin = true;
				temp->setGenerate(false);
				return tempContainer;
			}
			else continue;
		}
	}
	tempContainer.isGenerate = false;
	tempContainer.x = 0;
	tempContainer.y = 0;
	tempContainer.isSmallSun = false;
	return tempContainer;
}

void PlantManager::setStage(int num) {
	_stageNum = num;
	if (_stageNum == 0 || _stageNum == 1) _currentTile = 63;
	else _currentTile = 55;
}
