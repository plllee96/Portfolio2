#include "Stdafx.h"
#include "TubeZombie.h"

HRESULT TubeZombie::init(ZombieType type, int line) {
	Zombie::init(type, line);
	_image = IMAGEMANAGER->addFrameImage("TubeZombie", "Resources/Images/Zombies/TubeZombie.bmp", 264, 360, 4, 4, true, RGB(255, 0, 255));
	_x = WINSIZE_X;
	_rc = _recognizeRc = RectMake(_x, startY + _line * _tileHeight - fixY, _image->getFrameWidth(), _image->getFrameHeight());
	_hp = 10.0f;
	_status = TubeZombieStatus::WALK;
	_speed = 0.05f;
	return S_OK;
}

void TubeZombie::release(void) {
	Zombie::release();
}

void TubeZombie::update(void) {
	Zombie::update();
	if (_x <= 490) _status = TubeZombieStatus::SWIM;
	act();
	setFrame();
	updateFrame();
	attack();
	_rc = _recognizeRc = RectMake(_x, startY + _line * _tileHeight - fixY + 40, _image->getFrameWidth(), _image->getFrameHeight() - 60);

}

void TubeZombie::render(void) {
	_image->frameRender(getMemDC(), _rc.left - 10, _rc.top - 40, _frame.currentFrameX, _frame.currentFrameY);
}

void TubeZombie::act() {
	if (_status == TubeZombieStatus::WALK || _status == TubeZombieStatus::SWIM) _x -= _speed;

	if (_hp <= 0.0f) {
		if (_status == TubeZombieStatus::DEAD) return;

		if (_hp <= -50.0f) _active = false;
		else _status = TubeZombieStatus::DEAD;
	}
}

void TubeZombie::attack() {
}

void TubeZombie::collideObject(ObserveData obData) {
	if (*obData.type == ObservedType::BULLET && *obData.hitActive) {
		_hp -= *obData.damage;
	}
}

void TubeZombie::recognizeObject(ObserveData observer) {
}

void TubeZombie::setFrame() {
	switch (_status) {
		case TubeZombieStatus::WALK: {
			_frame.maxFrameX = 4;
			_frame.coolTime = 0.3f;
			_frame.currentFrameY = 0;
		} break;
		case TubeZombieStatus::SWIM: {
			_frame.maxFrameX = 4;
			_frame.coolTime = 0.3f;
			if (_hp <= 5) _frame.currentFrameY = 2;
			else _frame.currentFrameY = 1;
		} break;
		case TubeZombieStatus::DEAD: {
			_frame.maxFrameX = 4;
			_frame.coolTime = 0.3f;
			_frame.currentFrameY = 3;
		} break;
	}
}

void TubeZombie::updateFrame() {
	if (_frame.count + _frame.coolTime < TIMEMANAGER->getWorldTime()) {
		_frame.count = TIMEMANAGER->getWorldTime();
		if (_frame.currentFrameX >= _frame.maxFrameX - 1) {
			if (_status == TubeZombieStatus::DEAD) _active = false;
			else _frame.currentFrameX = 0;
		}
		else {
			_frame.currentFrameX += 1;
		}
	}
}
