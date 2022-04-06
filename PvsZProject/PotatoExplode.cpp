#include "Stdafx.h"
#include "PotatoExplode.h"

HRESULT PotatoExplode::init(BulletType type, int x, int y, int line) {
	Bullet::init(type, x, y, line);
	_image = IMAGEMANAGER->addFrameImage("PotatoExplode", "Resources/Images/Plants/Bullet/PotatoMine_Explode.bmp", 1280, 120, 8, 1, true, RGB(255, 0, 255));
	_damage = 99999.0f;
	_rc = _recognizeRc = RectMake(x + 40, y + 30, _image->getFrameWidth() /2, _image->getFrameHeight() /2);
	_damageType = DamageType::EXPLODE;

	_count = TIMEMANAGER->getWorldTime();
	_coolTime = 0.1f;
	_frame = 0;

	return S_OK;
}

void PotatoExplode::release(void) {
	Bullet::release();
}

void PotatoExplode::update(void) {
	if (_count + _coolTime < TIMEMANAGER->getWorldTime()) {
		_frame += 1;
		_count = TIMEMANAGER->getWorldTime();
	}
	if (_frame >= _image->getMaxFrameX()) {
		_active = false;
	}

}

void PotatoExplode::render(void) {
	_image->frameRender(getMemDC(), _x, _y, _frame, 0);
}

void PotatoExplode::collideObject(ObserveData obData) {
}

void PotatoExplode::recognizeObject(ObserveData observer) {
}
