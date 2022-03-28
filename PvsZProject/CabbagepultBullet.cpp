#include "Stdafx.h"
#include "CabbagepultBullet.h"

HRESULT CabbagepultBullet::init(BulletType type, int x, int y, int line) {
	Bullet::init(type, x, y, line);
	_image = IMAGEMANAGER->addFrameImage("Cabbagepult_Bullet", "Resources/Images/Plants/Bullet/Cabbagepult_Bullet.bmp", 24, 24, 1, 1, true, RGB(255, 0, 255));
	_damage = 2.0f;
	_rc = _recognizeRc = RectMake(x, y, _image->getFrameWidth(), _image->getFrameHeight());
	_gravityY = 0.0f;

	_startX = x;
	return S_OK;
}

void CabbagepultBullet::release(void) {
	Bullet::release();
}

void CabbagepultBullet::update(void) {
	if (_x > WINSIZE_X) _active = false;
	_x += 3;
	_rc = _recognizeRc = RectMake(_x, _y + 15, _image->getFrameWidth(), _image->getFrameHeight() - 10);
	setGravityY();
}

void CabbagepultBullet::render(void) {
	_image->frameRender(getMemDC(), _x, _y - _gravityY, 0, 0);
}

void CabbagepultBullet::collideObject(ObserveData obData) {
	if (*obData.type == ObservedType::ZOMBIE) _active = false;
}

void CabbagepultBullet::recognizeObject(ObserveData observer) {
}

void CabbagepultBullet::setGravityY() {

}
