#include "Stdafx.h"
#include "MushroomBullet.h"

HRESULT MushroomBullet::init(BulletType type, int x, int y, int line) {
	Bullet::init(type, x, y, line);
	_image = IMAGEMANAGER->addFrameImage("PuffShroomBullet", "Resources/Images/Plants/Bullet/PuffShroom_Bullet.bmp", 528, 52, 6, 1, true, RGB(255, 0, 255));
	_damage = 1.0f;
	_rc = _recognizeRc = RectMake(x, y, _image->getFrameWidth(), _image->getFrameHeight());

	return S_OK;
}

void MushroomBullet::release(void) {
	Bullet::release();
}

void MushroomBullet::update(void) {
	_x += 2;
	_rc = _recognizeRc = RectMake(_x, _y, _image->getFrameWidth() / 2, _image->getFrameHeight() / 2);
}

void MushroomBullet::render(void) {
	_image->frameRender(getMemDC(), _x, _y, 0, 0);
}

void MushroomBullet::collideObject(ObserveData obData) {
	if (*obData.type == ObservedType::ZOMBIE) _active = false;
}

void MushroomBullet::recognizeObject(ObserveData observer) {
}
