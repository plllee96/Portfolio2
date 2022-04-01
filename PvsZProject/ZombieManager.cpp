#include "Stdafx.h"
#include "ZombieManager.h"

HRESULT ZombieManager::init(void) {
	return S_OK;
}

void ZombieManager::release(void) {
}

void ZombieManager::update(void) {
	_viZombie = _vZombie.begin();
	for (; _viZombie != _vZombie.end(); ++_viZombie) {
		(*_viZombie)->update();

		if (!(*_viZombie)->isActive()) {
			if (((*_viZombie)->getType() == ZombieType::CORNHEAD_ZOMBIE || (*_viZombie)->getType() == ZombieType::BUCKETHEAD_ZOMBIE)
				&& ((_stageNum == 2 || _stageNum == 3) && !((*_viZombie)->getLine() == 2 || (*_viZombie)->getLine() == 3))) {
				int tempLine = (*_viZombie)->getLine();
				int tempX = (*_viZombie)->getX();
				removeZombie(_viZombie);
				addZombie(tempLine, tempX);
				break;
			}
			else {
				_lastZombiePosition.x = (*_viZombie)->getX();
				_lastZombiePosition.y = (*_viZombie)->getY();
				removeZombie(_viZombie);
			}
			break;
		}
	}
}

void ZombieManager::render(void) {
	_viZombie = _vZombie.begin();
	for (; _viZombie != _vZombie.end(); ++_viZombie) {
		if((*_viZombie)->getLine() == 0) (*_viZombie)->render();
	}
	_viZombie = _vZombie.begin();
	for (; _viZombie != _vZombie.end(); ++_viZombie) {
		if ((*_viZombie)->getLine() == 1) (*_viZombie)->render();
	}
	_viZombie = _vZombie.begin();
	for (; _viZombie != _vZombie.end(); ++_viZombie) {
		if ((*_viZombie)->getLine() == 2) (*_viZombie)->render();
	}
	_viZombie = _vZombie.begin();
	for (; _viZombie != _vZombie.end(); ++_viZombie) {
		if ((*_viZombie)->getLine() == 3) (*_viZombie)->render();
	}
	_viZombie = _vZombie.begin();
	for (; _viZombie != _vZombie.end(); ++_viZombie) {
		if ((*_viZombie)->getLine() == 4) (*_viZombie)->render();
	}
	_viZombie = _vZombie.begin();
	for (; _viZombie != _vZombie.end(); ++_viZombie) {
		if ((*_viZombie)->getLine() == 5) (*_viZombie)->render();
	}
}

void ZombieManager::addZombie(ZombieType type, int line) {
	Zombie* temp;
	if ((_stageNum == 2 || _stageNum == 3) && (line == 2 || line == 3)) {
		
		temp = new TubeZombie;
	}
	else {
		switch (type) {
			case ZombieType::ZOMBIE: temp = new NormalZombie; break;
			case ZombieType::CORNHEAD_ZOMBIE: temp = new CornheadZombie; break;
			case ZombieType::BUCKETHEAD_ZOMBIE: temp = new BucketheadZombie; break;
				//add ZombieType Here

			default: temp = new Zombie;
		}
	}
	temp->setTileHeight(_tileHeight);
	temp->init(type, line);
	_vZombie.push_back(temp);
}

void ZombieManager::addZombie(int line, int x) {
	// ! Only NormalZombie
	Zombie* temp = new NormalZombie;
	temp->setTileHeight(_tileHeight);
	temp->init(ZombieType::ZOMBIE, line);
	temp->setX(x);
	_vZombie.push_back(temp);
}

void ZombieManager::removeZombie(int index) {
	_vZombie[index]->release();
	_vZombie.erase(_vZombie.begin() + index);
}

void ZombieManager::removeZombie(viZombie iter) {
	(*iter)->release();
	_vZombie.erase(iter);
}

void ZombieManager::setStage(int stageNum) {
	_stageNum = stageNum;
	if (_stageNum == 0 || _stageNum == 1) _tileHeight = 63;
	else _tileHeight = 55;
}
