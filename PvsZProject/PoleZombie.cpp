#include "Stdafx.h"
#include "PoleZombie.h"

HRESULT PoleZombie::init(ZombieType type, int line) {
	Zombie::init(type, line);
	_image = IMAGEMANAGER->addFrameImage("PoleZombie", "Resources/Images/Zombies/PoleZombie.bmp", 1312, 1440, 8, 10, true, RGB(255, 0, 255));
	_x = WINSIZE_X;
	_rc = _recognizeRc = RectMake(_x, startY + _line * _tileHeight - fixY, _image->getFrameWidth(), _image->getFrameHeight());
	_hp = 10.0f;
	_status = PoleZombieStatus::RUN;

	return S_OK;
}

void PoleZombie::release(void) {
	Zombie::release();
}

void PoleZombie::update(void) {
	Zombie::update();
	act();
	setFrame();
	updateFrame();
	attack();
	_rc = _recognizeRc = RectMake(_x, startY + _line * _tileHeight - fixY + 40, _image->getFrameWidth() - 120, _image->getFrameHeight() - 100);
}

void PoleZombie::render(void) {
	_image->frameRender(getMemDC(), _rc.left - 80, _rc.top - 100, _frame.currentFrameX, _frame.currentFrameY);
}

void PoleZombie::act() {
	if (_status == PoleZombieStatus::RUN) _x -= 0.08f;
	else if (_status == PoleZombieStatus::JUMP) _x -= 0.4f;
	else if (_status == PoleZombieStatus::WALK) _x -= 0.05f;

	if (_hp <= 0.0f) {
		if (_status == PoleZombieStatus::DEAD) return;
		else {
			_status = PoleZombieStatus::DEAD;
			_frame.currentFrameX = 0;
		}
	}
}

void PoleZombie::attack() {
	if (_status == PoleZombieStatus::ATTACK) {
		if (_frame.currentFrameX == 2 || _frame.currentFrameX == 6) {
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

void PoleZombie::collideObject(ObserveData obData) {
	if (*obData.type == ObservedType::BULLET && *obData.hitActive) {
		if (_status != PoleZombieStatus::JUMP) _hp -= *obData.damage;
	}
}

void PoleZombie::recognizeObject(ObserveData observer) {
	if (_status == PoleZombieStatus::RUN) {
		_status = PoleZombieStatus::JUMP;
		_frame.currentFrameX = 0;
	}
	else if (_status == PoleZombieStatus::WALK) {
		_status = PoleZombieStatus::ATTACK;
		_frame.currentFrameX = 0;
	}
}

void PoleZombie::setFrame() {
	switch (_status) {
		case PoleZombieStatus::WAIT: {
			_frame.maxFrameX = 4;
			_frame.coolTime = 0.5f;
			_frame.currentFrameY = 0;
		} break;
		case PoleZombieStatus::RUN: {
			_frame.maxFrameX = 8;
			_frame.coolTime = 0.1f;
			if (_hp <= 5) _frame.currentFrameY = 2;
			else _frame.currentFrameY = 1;
		} break;
		case PoleZombieStatus::JUMP: {
			_frame.maxFrameX = 6;
			_frame.coolTime = 0.2f;
			if (_hp <= 5) _frame.currentFrameY = 4;
			else _frame.currentFrameY = 3;
		} break;
		case PoleZombieStatus::WALK: {
			_frame.maxFrameX = 7;
			_frame.coolTime = 0.3f;
			if (_hp <= 5) _frame.currentFrameY = 6;
			else _frame.currentFrameY = 5;
		} break;
		case PoleZombieStatus::ATTACK: {
			_frame.maxFrameX = 7;
			_frame.coolTime = 0.15f;
			if (_hp <= 5) _frame.currentFrameY = 8;
			else _frame.currentFrameY = 7;
		} break;
		case PoleZombieStatus::DEAD: {
			_frame.maxFrameX = 13;
			_frame.coolTime = 0.15f;
			_frame.currentFrameY = 9;
		} break;
	}
}

void PoleZombie::updateFrame() {
	if (_frame.count + _frame.coolTime < TIMEMANAGER->getWorldTime()) {
		_frame.count = TIMEMANAGER->getWorldTime();
		if (_frame.currentFrameX >= _frame.maxFrameX - 1) {
			if (_status == PoleZombieStatus::DEAD) _active = false;
			if (_status == PoleZombieStatus::ATTACK) {
				_status = PoleZombieStatus::WALK;
			}
			else if (_status == PoleZombieStatus::JUMP) {
				_status = PoleZombieStatus::WALK;
			}
			else _frame.currentFrameX = 0;
		}
		else {
			_frame.currentFrameX += 1;
		}
	}
}
