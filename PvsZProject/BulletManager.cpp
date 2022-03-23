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
	Bullet* temp;
	switch (type) {
		case BulletType::PEASHOOTER_BULLET: temp = new PeashooterBullet; break;
		case BulletType::CHERRY_EXPLODE: temp = new CherryExplode; break;
		case BulletType::POTATO_EXPLODE: temp = new PotatoExplode; break;

		case BulletType::INVISIBLE_RECT: temp = new InvisibleRect; break;
		default: temp = new Bullet;
	}
	temp->init(type, x, y, line);
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
