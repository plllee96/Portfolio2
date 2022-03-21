#include "Stdafx.h"
#include "Bullet.h"

HRESULT Bullet::init(BulletType type, int x, int y) {
	OBSERVERMANAGER->registerObserver(this);

	_type = type;
	_obType = ObservedType::BULLET;
	_damageType = DamageType::NONE;
	_x = x;
	_y = y;
	_active = true;

	return S_OK;
}

void Bullet::release(void) {
}

void Bullet::update(void) {
	cout << "Bullet::update" << endl;
}

void Bullet::render(void) {
}

ObserveData Bullet::getRectUpdate() {
	ObserveData temp;
	temp.type = &_obType;
	temp.damageType = &_damageType;
	temp.rc = &_rc;
	temp.recognizeRc = &_recognizeRc;
	temp.damage = &_damage;
	temp.hitActive = &_hitActive;
	return temp;
}

void Bullet::collideObject(ObserveData obData) {
}

void Bullet::recognizeObject(ObserveData observer) {
}
