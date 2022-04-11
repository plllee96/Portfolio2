#include "Stdafx.h"
#include "Plant.h"

HRESULT Plant::init(PlantType type, POINT location) {
	//init Observer
	OBSERVERMANAGER->registerObserver(this);
	OBSERVERMANAGER->registerBulletObserver(this);

	//init Basic Data
	_obType = ObservedType::PLANT;
	_bulletObType = BulletObservedType::OBJECT;

	_type = type;
	_location = location;
	_line = location.y;
	_hp = 5.0f;
	_active = true;
	_hitActive = true;

	//init Frame
	_frame.maxFrameX = 1;
	_frame.currentFrameX = 0;
	_frame.currentFrameY = 0;
	_frame.count = TIMEMANAGER->getWorldTime();
	_frame.coolTime = 0.5f;



	return S_OK;
}

void Plant::release(void) {
	OBSERVERMANAGER->removeObserver(this);
	OBSERVERMANAGER->removeBulletObserver(this);
}

void Plant::update(void) {
	if (_hp <= 0.0f) _active = false;
	act();
}

void Plant::render(void) {
}

ObserveData Plant::getRectUpdate() {
	ObserveData temp;
	temp.plantType = &_type;
	temp.rc = &_rc;
	temp.recognizeRc = &_recognizeRc;
	temp.type = &_obType;
	temp.line = &_line;
	temp.hitActive = &_hitActive;
	return temp;
}

void Plant::collideObject(ObserveData obData) {
	if (obData.hitActive) {
		_hp -= *obData.damage;
	}
}

void Plant::recognizeObject(ObserveData observer) {
	// ! Do Nothing
}

BulletObserveData Plant::getFireUpdate() {
	BulletObserveData temp;
	temp.type = &_bulletObType;
	temp.bulletType = &_bulletType;
	temp.plantType = &_type;
	temp.x = &_fireX;
	temp.y = &_fireY;
	temp.fire = &_fire;
	temp.line = &_line;

	return temp;
}

void Plant::fireObject(BulletObserveData observer) {
	// ! Do Nothing
}

void Plant::fireObject(BulletObserveData observer, RECT rc) {
	// ! Do Nothing
}

void Plant::act() {
	// ! Do Nothing
}
