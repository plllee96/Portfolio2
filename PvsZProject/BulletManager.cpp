#include "Stdafx.h"
#include "BulletManager.h"

HRESULT BulletManager::init(void) {
	return S_OK;
}

void BulletManager::release(void) {
}

void BulletManager::update(void) {
	_viBullet = _vBullet.begin();
		for (; _viBullet != _vBullet.end(); ++_viBullet) {
			(*_viBullet)->update();
	}
}

void BulletManager::render(void) {
	_viBullet = _vBullet.begin();
	for (; _viBullet != _vBullet.end(); ++_viBullet) {
		(*_viBullet)->render();
	}
}

void BulletManager::addBullet(BulletType type, int x, int y) {
	Bullet* temp;
	switch (type) {
		case BulletType::PEASHOOTER_BULLET: temp = new PeashooterBullet; break;
		default: temp = new Bullet;
	}
	temp->init(type, x, y);

}

void BulletManager::removeBullet(viBullet iter) {
}
