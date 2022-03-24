#include "Stdafx.h"
#include "NormalZombie.h"

HRESULT NormalZombie::init(ZombieType type, int line) {
	Zombie::init(type, line);
	_image = IMAGEMANAGER->addFrameImage("NormalZombie", "Resources/Images/Zombies/Zombie.bmp", 910, 700, 13, 7, true, RGB(255, 0, 255));
	_x = WINSIZE_X;
	_rc = _recognizeRc = RectMake(_x, startY + _line * firstMapTileHeight - fixY, _image->getFrameWidth(), _image->getFrameHeight());
	_hp = 10.0f;
	_status = NormalZombieStatus::WALK;

	return S_OK;
}

void NormalZombie::release(void) {
	Zombie::release();
}

void NormalZombie::update(void) {
	Zombie::update();
	act();
	setFrame();
	updateFrame();
	attack();
	_rc = _recognizeRc = RectMake(_x, startY + _line * firstMapTileHeight - fixY + 40, _image->getFrameWidth(), _image->getFrameHeight() - 60);
}

void NormalZombie::render(void) {
	_image->frameRender(getMemDC(), _rc.left - 10, _rc.top - 40, _frame.currentFrameX, _frame.currentFrameY);
}

void NormalZombie::act() {
	if (_status == NormalZombieStatus::WALK) _x -= 0.05f;

	if (_hp <= 0.0f) {
		if (_status == NormalZombieStatus::DEAD || _status == NormalZombieStatus::EXPLODE) return;

		if (_hp <= -10000.0f) _active = false;
		else if (_hp <= -50.0f) {
			if (_status != NormalZombieStatus::EXPLODE) _frame.currentFrameX = 0;
			_status = NormalZombieStatus::EXPLODE;
		}
		else _status = NormalZombieStatus::DEAD;
	}
}

void NormalZombie::attack() {
	if (_status == NormalZombieStatus::ATTACK) {
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

void NormalZombie::collideObject(ObserveData obData) {
	if (*obData.type == ObservedType::BULLET && *obData.hitActive) {
		_hp -= *obData.damage;
	}
}

void NormalZombie::recognizeObject(ObserveData observer) {
	if (_status == NormalZombieStatus::WALK) {
		_status = NormalZombieStatus::ATTACK;
		_frame.currentFrameX = 0;
	}
}

void NormalZombie::setFrame() {
	switch (_status) {
		case NormalZombieStatus::WAIT: {
			_frame.maxFrameX = 4;
			_frame.coolTime = 0.5f;
			_frame.currentFrameY = 0;
		} break;
		case NormalZombieStatus::WALK: {
			_frame.maxFrameX = 7;
			_frame.coolTime = 0.3f;
			if(_hp <= 5) _frame.currentFrameY = 3;
			else _frame.currentFrameY = 1;
		} break;
		case NormalZombieStatus::ATTACK: {
			_frame.maxFrameX = 7;
			_frame.coolTime = 0.15f;
			if (_hp <= 5) _frame.currentFrameY = 4;
			else _frame.currentFrameY = 2;
		} break;
		case NormalZombieStatus::DEAD: {
			_frame.maxFrameX = 13;
			_frame.coolTime = 0.15f;
			_frame.currentFrameY = 5;
		} break;
		case NormalZombieStatus::EXPLODE: {
			_frame.maxFrameX = 2;
			_frame.coolTime = 1.0f;
			_frame.currentFrameY = 6;
		} break;
	}
}

void NormalZombie::updateFrame() {
	if (_frame.count + _frame.coolTime < TIMEMANAGER->getWorldTime()) {
		_frame.count = TIMEMANAGER->getWorldTime();
		if (_frame.currentFrameX >= _frame.maxFrameX - 1) {
			if (_status == NormalZombieStatus::DEAD || _status == NormalZombieStatus::EXPLODE) _active = false;
			if (_status == NormalZombieStatus::ATTACK) {
				_status = NormalZombieStatus::WALK;
			}
			else _frame.currentFrameX = 0;
		}
		else {
			_frame.currentFrameX += 1;
		}
	}
}
