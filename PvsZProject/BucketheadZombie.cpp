#include "Stdafx.h"
#include "BucketheadZombie.h"

HRESULT BucketheadZombie::init(ZombieType type, int line) {
	Zombie::init(type, line);
	_image = IMAGEMANAGER->addFrameImage("BucketheadZombie", "Resources/Images/Zombies/BucketheadZombie.bmp", 476, 530, 7, 5, true, RGB(255, 0, 255));
	_x = WINSIZE_X;
	_rc = _recognizeRc = RectMake(_x, startY + _line * _tileHeight - fixY, _image->getFrameWidth(), _image->getFrameHeight());
	_hp = 28.0f;
	_status = BucketheadZombieStatus::WALK;

	return S_OK;
}

void BucketheadZombie::release(void) {
	Zombie::release();
}

void BucketheadZombie::update(void) {
	Zombie::update();
	act();
	setFrame();
	updateFrame();
	attack();
	_rc = _recognizeRc = RectMake(_x, startY + _line * _tileHeight - fixY + 40, _image->getFrameWidth(), _image->getFrameHeight() - 60);
}

void BucketheadZombie::render(void) {
	_image->frameRender(getMemDC(), _rc.left - 15, _rc.top - 55, _frame.currentFrameX, _frame.currentFrameY);
}

void BucketheadZombie::act() {
	if (_status == BucketheadZombieStatus::WALK) _x -= 0.05f;

	if (_hp <= 0.0f) {
		if (_hp > -50.0f) {
			if (!_objectAlreadyFall) {
				_objectFall = true;
				_objectAlreadyFall = true;
			}
			if (_objectAlreadyFall) {
				_active = false;
			}
		}
		else {
			_active = false;
		}
	}
}

void BucketheadZombie::attack() {
	if (_status == BucketheadZombieStatus::ATTACK) {
		if (_frame.currentFrameX == 1 || _frame.currentFrameX == 4) {
			_attack = true;
		}
		else {
			_attack = false;
		}
	}
	else {
		_attack = false;
	}
}

void BucketheadZombie::collideObject(ObserveData obData) {
	if (*obData.type == ObservedType::BULLET && *obData.hitActive) {
		_hp -= *obData.damage;
	}
}

void BucketheadZombie::recognizeObject(ObserveData observer) {
	if (*observer.plantType == PlantType::WALLNUTBOWLING) {
		if (*observer.hitActive) {
			_hp -= 25.0f;
		}
		return;
	}
	if (_status == BucketheadZombieStatus::WALK) {
		_status = BucketheadZombieStatus::ATTACK;
		_frame.currentFrameX = 0;
	}
}

void BucketheadZombie::setFrame() {
	switch (_status) {
		case BucketheadZombieStatus::WAIT: {
			_frame.maxFrameX = 4;
			_frame.coolTime = 0.5f;
			_frame.currentFrameY = 0;
		} break;
		case BucketheadZombieStatus::WALK: {
			_frame.maxFrameX = 7;
			_frame.coolTime = 0.3f;
			if (_hp <= 7) _frame.currentFrameY = 2;
			else _frame.currentFrameY = 1;
		} break;
		case BucketheadZombieStatus::ATTACK: {
			_frame.maxFrameX = 7;
			_frame.coolTime = 0.15f;
			if (_hp <= 7) _frame.currentFrameY = 4;
			else _frame.currentFrameY = 3;
		} break;
	}
}

void BucketheadZombie::updateFrame() {
	if (_frame.count + _frame.coolTime < TIMEMANAGER->getWorldTime()) {
		_frame.count = TIMEMANAGER->getWorldTime();
		if (_frame.currentFrameX >= _frame.maxFrameX - 1) {
			if (_status == BucketheadZombieStatus::ATTACK) {
				_status = BucketheadZombieStatus::WALK;
			}
			else _frame.currentFrameX = 0;
		}
		else {
			_frame.currentFrameX += 1;
		}
	}
}
