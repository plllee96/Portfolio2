#include "Stdafx.h"
#include "PeashooterBullet.h"

HRESULT PeashooterBullet::init(BulletType type, int x, int y, int line) {
	Bullet::init(type, x, y, line);
	_image = IMAGEMANAGER->addFrameImage("PeashooterBullet", "Resources/Images/Plants/Bullet/Peashooter_Bullet.bmp", 84, 34, 3, 1, true, RGB(255, 0, 255));
	_fireImage = IMAGEMANAGER->addFrameImage("Torchwood_Bullet", "Resources/Images/Plants/Bullet/Torchwood_Bullet.bmp", 210, 34, 5, 1, true, RGB(255, 0, 255));
	_damage = 1.0f;
	_rc = _recognizeRc = RectMake(x, y, _image->getFrameWidth(), _image->getFrameHeight());

	return S_OK;
}

void PeashooterBullet::release(void) {
	Bullet::release();
}

void PeashooterBullet::update(void) {
	if (_x > WINSIZE_X) _active = false;
	_x += 2;
	_rc = _recognizeRc = RectMake(_x, _y + 15, _image->getFrameWidth(), _image->getFrameHeight() - 10);
}

void PeashooterBullet::render(void) {
	if (_isFire) _fireImage->frameRender(getMemDC(), _x, _y, 0, 0);
	else _image->frameRender(getMemDC(), _x, _y, 0, 0);
}

void PeashooterBullet::collideObject(ObserveData obData) {
	if (*obData.type == ObservedType::ZOMBIE) _active = false;

	else if (*obData.type == ObservedType::PLANT) {
		if (*obData.plantType == PlantType::TORCHWOOD) {
			_isFire = true;
			_damage = 2.0f;
		}
	}
}

void PeashooterBullet::recognizeObject(ObserveData observer) {
}
