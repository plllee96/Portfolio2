#include "Stdafx.h"
#include "FumeshroomBullet.h"

HRESULT FumeshroomBullet::init(BulletType type, int x, int y, int line) {
	Bullet::init(type, x, y, line);
	_image = IMAGEMANAGER->addFrameImage("FumeShroom_Bullet", "Resources/Images/Plants/Bullet/FumeShroom_Bullet.bmp", 1926, 62, 9, 1, true, RGB(255, 0, 255));
	_damage = 0.1f;
	_rc = _recognizeRc = RectMake(x, y + _image->getFrameHeight() / 2, _image->getFrameWidth(), _image->getFrameHeight() / 2);

	_count = TIMEMANAGER->getWorldTime();
	_coolTime = 0.08f;
	_frame = 0;

	return S_OK;
}

void FumeshroomBullet::release(void) {
	Bullet::release();
}

void FumeshroomBullet::update(void) {
	(_frame == 0) ? _hitActive = true : _hitActive = false;
	updateFrame();
}

void FumeshroomBullet::render(void) {
	_image->frameRender(getMemDC(), _x, _y, _frame, 0);
}

void FumeshroomBullet::collideObject(ObserveData obData) {
}

void FumeshroomBullet::recognizeObject(ObserveData observer) {
}

void FumeshroomBullet::updateFrame() {
	if (_count + _coolTime < TIMEMANAGER->getWorldTime()) {
		_frame += 1;
		_count = TIMEMANAGER->getWorldTime();
	}
	if (_frame > _image->getMaxFrameX()) {
		_active = false;
	}
}
