#include "Stdafx.h"
#include "CherryExplode.h"

HRESULT CherryExplode::init(BulletType type, int x, int y, int line) {
	Bullet::init(type, x, y, line);
	_image = IMAGEMANAGER->addFrameImage("CherryExplode", "Resources/Images/Plants/Bullet/CherryBomb_Explode.bmp", 1520, 140, 8, 1, true, RGB(255, 0, 255));
	_damage = 999.0f;
	_rc = _recognizeRc = RectMake(x, y, _image->getFrameWidth(), _image->getFrameHeight());
	_damageType = DamageType::EXPLODE;
	
	
	_count = TIMEMANAGER->getWorldTime();
	_coolTime = 0.1f;
	_frame = 0;

	return S_OK;
}

void CherryExplode::release(void) {
	Bullet::release();
}

void CherryExplode::update(void) {
	if (_count + _coolTime < TIMEMANAGER->getWorldTime()) {
		_frame += 1;
		_count = TIMEMANAGER->getWorldTime();
	}
	if (_frame > _image->getMaxFrameX()) {
		_active = false;
	}
}

void CherryExplode::render(void) {
	_image->frameRender(getMemDC(), _x, _y, _frame, 0);
}

void CherryExplode::collideObject(ObserveData obData) {

}

void CherryExplode::recognizeObject(ObserveData observer) {
}
