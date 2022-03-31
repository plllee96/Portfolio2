#include "Stdafx.h"
#include "CornheadZombie.h"

HRESULT CornheadZombie::init(ZombieType type, int line) {
	Zombie::init(type, line);
	_image = IMAGEMANAGER->addFrameImage("CornheadZombie", "Resources/Images/Zombies/CornheadZombie.bmp", 490, 550, 7, 5, true, RGB(255, 0, 255));
	_x = WINSIZE_X;
	_rc = _recognizeRc = RectMake(_x, startY + _line * _tileHeight - fixY, _image->getFrameWidth(), _image->getFrameHeight());
	_hp = 14.0f;
	_status = CornheadZombieStatus::WALK;

	return S_OK;
}

void CornheadZombie::release(void) {
	Zombie::release();
}

void CornheadZombie::update(void) {
	Zombie::update();
	act();
	setFrame();
	updateFrame();
	attack();
	_rc = _recognizeRc = RectMake(_x, startY + _line * _tileHeight - fixY + 40, _image->getFrameWidth(), _image->getFrameHeight() - 60);
}

void CornheadZombie::render(void) {
	_image->frameRender(getMemDC(), _rc.left - 12, _rc.top - 60, _frame.currentFrameX, _frame.currentFrameY);
}

void CornheadZombie::act() {
	if (_status == CornheadZombieStatus::WALK) _x -= 0.05f;

	if (_hp <= 0.0f) {
		_active = false;
	}
}

void CornheadZombie::attack() {
	if (_status == CornheadZombieStatus::ATTACK) {
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

void CornheadZombie::collideObject(ObserveData obData) {
	if (*obData.type == ObservedType::BULLET && *obData.hitActive) {
		_hp -= *obData.damage;
	}
}

void CornheadZombie::recognizeObject(ObserveData observer) {
	if (_status == CornheadZombieStatus::WALK) {
		_status = CornheadZombieStatus::ATTACK;
		_frame.currentFrameX = 0;
	}
}

void CornheadZombie::setFrame() {
	switch (_status) {
		case CornheadZombieStatus::WAIT: {
			_frame.maxFrameX = 4;
			_frame.coolTime = 0.5f;
			_frame.currentFrameY = 0;
		} break;
		case CornheadZombieStatus::WALK: {
			_frame.maxFrameX = 7;
			_frame.coolTime = 0.3f;
			if (_hp <= 7) _frame.currentFrameY = 2;
			else _frame.currentFrameY = 1;
		} break;
		case CornheadZombieStatus::ATTACK: {
			_frame.maxFrameX = 7;
			_frame.coolTime = 0.15f;
			if (_hp <= 7) _frame.currentFrameY = 4;
			else _frame.currentFrameY = 3;
		} break;
	}
}

void CornheadZombie::updateFrame() {
	if (_frame.count + _frame.coolTime < TIMEMANAGER->getWorldTime()) {
		_frame.count = TIMEMANAGER->getWorldTime();
		if (_frame.currentFrameX >= _frame.maxFrameX - 1) {
			if (_status == CornheadZombieStatus::ATTACK) {
				_status = CornheadZombieStatus::WALK;
			}
			else _frame.currentFrameX = 0;
		}
		else {
			_frame.currentFrameX += 1;
		}
	}
}
