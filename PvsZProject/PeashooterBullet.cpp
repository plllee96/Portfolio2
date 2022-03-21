#include "Stdafx.h"
#include "PeashooterBullet.h"

HRESULT PeashooterBullet::init(BulletType type, int x, int y) {
	Bullet::init(type, x, y);
	return S_OK;
}

void PeashooterBullet::release(void) {
}

void PeashooterBullet::update(void) {
	cout << "PeashooterBullet::update" << endl;;
}

void PeashooterBullet::render(void) {
}

ObserveData PeashooterBullet::getRectUpdate() {
	ObserveData temp;
	temp.rc = &_rc;
	temp.recognizeRc = &_recognizeRc;
	temp.type = &_obType;
	temp.damage = &_damage;
	return temp;
}

void PeashooterBullet::collideObject(ObserveData obData) {
}

void PeashooterBullet::recognizeObject(ObserveData observer) {
}
