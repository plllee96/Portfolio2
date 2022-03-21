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
			removeZombie(_viZombie);
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

}

void ZombieManager::addZombie(ZombieType type, int line) {
	Zombie* temp;
	switch (type) {
		case ZombieType::ZOMBIE: temp = new NormalZombie; break;
		//add ZombieType Here

		default: temp = new Zombie;
	}
	temp->init(type, line);
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
