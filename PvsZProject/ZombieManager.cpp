#include "Stdafx.h"
#include "ZombieManager.h"

HRESULT ZombieManager::init(void) {
	_em = new EffectManager;
	_em->init();
	return S_OK;
}

void ZombieManager::release(void) {
	_em->release();
}

void ZombieManager::update(void) {
	_em->update();

	_viZombie = _vZombie.begin();
	for (; _viZombie != _vZombie.end(); ++_viZombie) {
		(*_viZombie)->update();

		if ((*_viZombie)->isArmFall()) {
			_em->createArm("Arm", (*_viZombie)->getX() + 22, (*_viZombie)->getY() + 65);
			(*_viZombie)->setArmFall(false);
		}
		if ((*_viZombie)->isHeadFall()) {
			switch ((*_viZombie)->getType()) {
				case ZombieType::ZOMBIE: {
					_em->createObject("Head", (*_viZombie)->getX() + 2, (*_viZombie)->getY() + 25);
					(*_viZombie)->setHeadFall(false);
				} break;
				case ZombieType::POLE_ZOMBIE: {
					_em->createObject("PoleZombieHead", (*_viZombie)->getX() + 2, (*_viZombie)->getY() + 25);
					(*_viZombie)->setHeadFall(false);
				} break;
			}

		}
		if ((*_viZombie)->isObjectFall()) {
			switch ((*_viZombie)->getType()) {
				case ZombieType::CORNHEAD_ZOMBIE: {
					_em->createObject("Corn", (*_viZombie)->getX() + 2, (*_viZombie)->getY() + 25);
					(*_viZombie)->setObjectFall(false);
				} break;
				case ZombieType::BUCKETHEAD_ZOMBIE: {
					_em->createObject("Bucket", (*_viZombie)->getX() + 2, (*_viZombie)->getY() + 25);
					(*_viZombie)->setObjectFall(false);
				} break;
			}
		}
		if (!(*_viZombie)->isActive()) {
			if (((*_viZombie)->getType() == ZombieType::CORNHEAD_ZOMBIE || (*_viZombie)->getType() == ZombieType::BUCKETHEAD_ZOMBIE)
				&& ((_stageNum == 0 || _stageNum == 1) || ((_stageNum == 2 || _stageNum == 3) && !((*_viZombie)->getLine() == 2 || (*_viZombie)->getLine() == 3)))) {
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

	_em->render();
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
			case ZombieType::POLE_ZOMBIE: temp = new PoleZombie; break;
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
