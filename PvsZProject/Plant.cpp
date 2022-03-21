#include "Stdafx.h"
#include "Plant.h"

HRESULT Plant::init(PlantType type, POINT location) {
	//init Observer
	OBSERVERMANAGER->registerObserver(this);

	//init Basic Data
	_obType = ObservedType::PLANT;
	_type = type;
	_location = location;

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
}

void Plant::update(void) {
	act();
}

void Plant::render(void) {
}

ObserveData Plant::getRectUpdate() {
	ObserveData temp;
	temp.rc = &_rc;
	temp.recognizeRc = &_recognizeRc;
	temp.type = &_obType;
	return temp;
}

void Plant::collideObject(ObserveData obData) {
}

void Plant::recognizeObject(ObserveData observer) {
}

void Plant::act() {
}
