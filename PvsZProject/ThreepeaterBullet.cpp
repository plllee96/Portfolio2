#include "Stdafx.h"
#include "ThreepeaterBullet.h"

HRESULT ThreepeaterBullet::init(BulletType type, int x, int y, int line) {
	Bullet::init(type, x, y, line);
	_image = IMAGEMANAGER->addFrameImage("PeashooterBullet", "Resources/Images/Plants/Bullet/Peashooter_Bullet.bmp", 84, 34, 3, 1, true, RGB(255, 0, 255));
	_fireImage = IMAGEMANAGER->addFrameImage("Torchwood_Bullet", "Resources/Images/Plants/Bullet/Torchwood_Bullet.bmp", 210, 34, 5, 1, true, RGB(255, 0, 255));
	_damage = 1.0f;
	_rc = _recognizeRc = RectMake(x, y, _image->getFrameWidth(), _image->getFrameHeight());
	_moveY = 0;
	return S_OK;
}

void ThreepeaterBullet::release(void) {
	Bullet::release();
}

void ThreepeaterBullet::update(void) {
	_x += 2;
	if (_locate == -1) {
		if (_moveY > -52) {
			_moveY--;
			_y--;
		}
	}
	else if (_locate == 1) {
		if (_moveY < 52) {
			_moveY++;
			_y++;
		}
	}
	if (_x > WINSIZE_X) _active = false;
	_rc = _recognizeRc = RectMake(_x, _y + 15, _image->getFrameWidth(), _image->getFrameHeight() - 10);
}

void ThreepeaterBullet::render(void) {
	if (_isFire) _fireImage->frameRender(getMemDC(), _x, _y, 0, 0);
	else _image->frameRender(getMemDC(), _x, _y, 0, 0);
}

void ThreepeaterBullet::collideObject(ObserveData obData) {
	if (*obData.type == ObservedType::ZOMBIE) _active = false;

	else if (*obData.type == ObservedType::PLANT) {
		if (*obData.plantType == PlantType::TORCHWOOD) {
			_isFire = true;
			_damage = 2.0f;
		}
	}
}

void ThreepeaterBullet::recognizeObject(ObserveData observer) {
}
