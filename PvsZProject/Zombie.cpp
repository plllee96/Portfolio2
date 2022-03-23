#include "Stdafx.h"
#include "Zombie.h"

HRESULT Zombie::init(ZombieType type, int line) {
	//init Observer
	OBSERVERMANAGER->registerObserver(this);

	//init Basic Data
	_obType = ObservedType::ZOMBIE;
	_type = type;
	_line = line;
	_damage = 0.02f;
	_active = true;
	_attack = false;

	//init Frame
	_frame.maxFrameX = 1;
	_frame.currentFrameX = 0;
	_frame.currentFrameY = 0;
	_frame.count = TIMEMANAGER->getWorldTime();
	_frame.coolTime = 0.5f;

	return S_OK;
}

void Zombie::release(void) {
	OBSERVERMANAGER->removeObserver(this);
}

void Zombie::update(void) {
	act();
}

void Zombie::render(void) {
}

ObserveData Zombie::getRectUpdate() {
	ObserveData temp;
	temp.rc = &_rc;
	temp.recognizeRc = &_recognizeRc;
	temp.type = &_obType;
	temp.line = &_line;
	temp.hitActive = &_attack;
	temp.damage = &_damage;
	return temp;
}

void Zombie::collideObject(ObserveData obData) {
}

void Zombie::recognizeObject(ObserveData observer) {
}

void Zombie::act() {
}