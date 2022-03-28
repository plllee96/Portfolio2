#include "Stdafx.h"
#include "BulletManager.h"

HRESULT BulletManager::init(void) {
	_bulletObType = BulletObservedType::BULLETMANAGER;
	OBSERVERMANAGER->registerBulletObserver(this);
	return S_OK;
}

void BulletManager::release(void) {
	OBSERVERMANAGER->removeBulletObserver(this);
}

void BulletManager::update(void) {
	_viBullet = _vBullet.begin();
		for (; _viBullet != _vBullet.end(); ++_viBullet) {
			(*_viBullet)->update();
			if (!(*_viBullet)->isActive()) {
				removeBullet(_viBullet);
				break;
			}
	}
}

void BulletManager::render(void) {
	_viBullet = _vBullet.begin();
	for (; _viBullet != _vBullet.end(); ++_viBullet) {
		(*_viBullet)->render();
	}
}

void BulletManager::addBullet(BulletType type, int x, int y, int line) {
	if (type == BulletType::THREEPEATER_BULLET) {
		if (line != 0) {
			Bullet* temp1 = new ThreepeaterBullet;
			temp1->init(type, x, y, line - 1);
			temp1->setLocate(-1);
			_vBullet.push_back(temp1);
		}

		Bullet* temp2 = new ThreepeaterBullet;
		temp2->init(type, x, y, line);
		temp2->setLocate(0);
		_vBullet.push_back(temp2);

		if (line != 4 + _stageNum / 2) {
			Bullet* temp3 = new ThreepeaterBullet;
			temp3->init(type, x, y, line + 1);
			temp3->setLocate(1);
			_vBullet.push_back(temp3);
		}
	}
	else {
		Bullet* temp;
		switch (type) {
			case BulletType::PEASHOOTER_BULLET: temp = new PeashooterBullet; break;
			case BulletType::CHERRY_EXPLODE: temp = new CherryExplode; break;
			case BulletType::POTATO_EXPLODE: temp = new PotatoExplode; break;
			case BulletType::MUSHROOM_BULLET: temp = new MushroomBullet; break;
			case BulletType::INVISIBLE_RECT: temp = new InvisibleRect; break;
			case BulletType::FUMESHROOM_BULLET: temp = new FumeshroomBullet; break;
			case BulletType::JALAPENO_EXPLODE: temp = new JalapenoExplode; break;
			case BulletType::CABBAGEPULT_BULLET: temp = new CabbagepultBullet; break;
			default: temp = new Bullet;
		}
		temp->init(type, x, y, line);
		_vBullet.push_back(temp);
	}
}

void BulletManager::addBullet(BulletType type, int x, int y, int line, RECT rc) {
	if (type != BulletType::CABBAGEPULT_BULLET) return;
	Bullet* temp;
	temp = new CabbagepultBullet;
	temp->init(type, x, y, line);
	temp->setZombieRc(rc);
	_vBullet.push_back(temp);
	
}

void BulletManager::removeBullet(viBullet iter) {
	(*iter)->release();
	_vBullet.erase(iter);
}

BulletObserveData BulletManager::getFireUpdate() {
	BulletObserveData temp;
	temp.type = &_bulletObType;
	return temp;
}

void BulletManager::fireObject(BulletObserveData observer) {
	addBullet(*observer.bulletType, *observer.x, *observer.y, *observer.line);
}

void BulletManager::fireObject(BulletObserveData observer, RECT rc) {
	addBullet(*observer.bulletType, *observer.x, *observer.y, *observer.line, rc);
}
