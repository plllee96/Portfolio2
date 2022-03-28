#include "Stdafx.h"
#include "JalapenoExplode.h"

HRESULT JalapenoExplode::init(BulletType type, int x, int y, int line) {
	Bullet::init(type, x, y, line);
	_image = IMAGEMANAGER->addFrameImage("JelepenoExplode", "Resources/Images/Plants/Bullet/Jalapeno_Explode.bmp", 264, 72, 6, 1, true, RGB(255, 0, 255));
	_damage = 999.0f;
	_rc = _recognizeRc = RectMake(70, y + _image->getFrameHeight() / 3 * 2, WINSIZE_X, _image->getFrameHeight() / 3);
	_damageType = DamageType::EXPLODE;


	_count = TIMEMANAGER->getWorldTime();
	_coolTime = 0.1f;
	_frame = 0;

	return S_OK;
}

void JalapenoExplode::release(void) {
	Bullet::release();
}

void JalapenoExplode::update(void) {
	if (_count + _coolTime < TIMEMANAGER->getWorldTime()) {
		_frame += 1;
		_count = TIMEMANAGER->getWorldTime();
	}
	if (_frame > _image->getMaxFrameX()) {
		_active = false;
	}
}

void JalapenoExplode::render(void) {
	for (int i = 0; i < 9; i++) {
		_image->frameRender(getMemDC(), 70 + 52 * i, _y, _frame, 0);
	}
	
}

void JalapenoExplode::collideObject(ObserveData obData) {
}

void JalapenoExplode::recognizeObject(ObserveData observer) {
}
