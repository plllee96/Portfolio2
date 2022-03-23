#include "Stdafx.h"
#include "PotatoMine.h"

HRESULT PotatoMine::init(PlantType type, POINT location) {
	Plant::init(type, location);
	_image = IMAGEMANAGER->addFrameImage("PotatoMine", "Resources/Images/Plants/PotatoMine.bmp", 180, 180, 3, 3, true, RGB(255, 0, 255));
	_rc = _recognizeRc = RectMake(startX + _location.x * tileWidth - 3, startY + _location.y * firstMapTileHeight, tileWidth, firstMapTileHeight);

	_bulletType = BulletType::POTATO_EXPLODE;

	_fireX = _rc.left - 30;
	_fireY = _rc.top - 50;

	_status = PotatoStatus::LOAD;
	_readyCount = TIMEMANAGER->getWorldTime();

	_frame.maxFrameX = 6;
	_frame.coolTime = 0.3f;
	_frame.currentFrameY = 0;
	return S_OK;
}

void PotatoMine::release(void) {
	Plant::release();
}

void PotatoMine::update(void) {
	Plant::update();
	if (_status == PotatoStatus::LOAD) {
		if (_readyCount + _potatoReadyTime < TIMEMANAGER->getWorldTime()) {
			_status = PotatoStatus::READY;
		}
	}
	if (_fire) _active = false;
	setFrame();
	updateFrame();
}

void PotatoMine::render(void) {
	_image->frameRender(getMemDC(), _rc.left, _rc.top, _frame.currentFrameX, _frame.currentFrameY);
}

void PotatoMine::recognizeObject(ObserveData observer) {
	if (_status == PotatoStatus::WAIT) {
		_fire = true;
	}
}

BulletObserveData PotatoMine::getFireUpdate() {
	BulletObserveData temp;
	temp.type = &_bulletObType;
	temp.bulletType = &_bulletType;
	temp.x = &_fireX;
	temp.y = &_fireY;
	temp.fire = &_fire;
	temp.line = &_line;
	return temp;
}

void PotatoMine::fireObject(BulletObserveData observer) {
}

void PotatoMine::setFrame() {
	switch (_status) {
		case PotatoStatus::LOAD: {
			_frame.maxFrameX = 1;
			_frame.coolTime = 0.5f;
			_frame.currentFrameY = 0;
		} break;
		case PotatoStatus::READY: {
			_frame.maxFrameX = 3;
			_frame.coolTime = 0.3f;
			_frame.currentFrameY = 1;
		} break;
		case PotatoStatus::WAIT: {
			_frame.maxFrameX = 2;
			_frame.coolTime = 0.5f;
			_frame.currentFrameY = 2;
		} break;
	}
}

void PotatoMine::updateFrame() {
	if (_frame.count + _frame.coolTime < TIMEMANAGER->getWorldTime()) {
		_frame.count = TIMEMANAGER->getWorldTime();
		if (_frame.currentFrameX >= _frame.maxFrameX - 1) {
			if (_status == PotatoStatus::READY) {
				_status = PotatoStatus::WAIT;
			}
			_frame.currentFrameX = 0;
		}
		else _frame.currentFrameX += 1;
	}
}
