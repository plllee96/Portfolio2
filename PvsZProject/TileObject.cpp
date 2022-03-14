#include "Stdafx.h"
#include "TileObject.h"

HRESULT TileObject::init(int amount, unsigned short x, unsigned short y) {
	_x = x;
	_y = y;
	for (int i = 0; i < amount; i++) {
		tagObject object;
		ZeroMemory(&object, sizeof(tagObject));
		object.image = new Image;
		object.image->init("Resources/Images/Rocket.bmp", 52, 60, true, RGB(255, 0, 255));
		unsigned short tempPosX = RND->getInt(x);
		unsigned short tempPosY = RND->getInt(y);
		object.rc = RectMake(TOPLEFT_X + tempPosX * TILESIZE, TOPLEFT_Y + tempPosY * TILESIZE, TILESIZE, TILESIZE);
		object.centerPos = object.tempPos = { object.rc.left + (object.rc.right - object.rc.left) / 2, object.rc.top + (object.rc.bottom - object.rc.top) / 2 };
		object.select = false;
		_vObject.push_back(object);
	}

	return S_OK;
}

void TileObject::release(void) {
}

void TileObject::update(void) {
	for (_viObject = _vObject.begin(); _viObject != _vObject.end(); ++_viObject) {
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && PtInRect(&_viObject->rc, _ptMouse)) {
			_viObject->tempPos = _viObject->centerPos;
			_viObject->select = true;
		}
		else if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && _viObject->select) {
			_viObject->centerPos = _ptMouse;
			
			_viObject->rc.left = _viObject->centerPos.x - TILESIZE / 2;
			_viObject->rc.right = _viObject->centerPos.x + TILESIZE / 2;
			_viObject->rc.top = _viObject->centerPos.y - TILESIZE / 2;
			_viObject->rc.bottom = _viObject->centerPos.y + TILESIZE / 2;

		}
		else if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && _viObject->select) {
			if (_viObject->centerPos.x < TOPLEFT_X - TILESIZE || _viObject->centerPos.x > TOPLEFT_X + (_x)*TILESIZE
				|| _viObject->centerPos.y < TOPLEFT_Y - TILESIZE || _viObject->centerPos.y > TOPLEFT_Y + (_y)*TILESIZE) {
				_viObject->centerPos.x = _viObject->tempPos.x;
				_viObject->centerPos.y = _viObject->tempPos.y;
				_viObject->rc.left = _viObject->centerPos.x - TILESIZE / 2;
				_viObject->rc.right = _viObject->centerPos.x + TILESIZE / 2;
				_viObject->rc.top = _viObject->centerPos.y - TILESIZE / 2;
				_viObject->rc.bottom = _viObject->centerPos.y + TILESIZE / 2;
			}
			else {
				_viObject->centerPos.x = TOPLEFT_X + TILESIZE / 2 + ((_viObject->centerPos.x - TOPLEFT_X)/TILESIZE)*TILESIZE;
				_viObject->centerPos.y = TOPLEFT_Y + TILESIZE / 2 + ((_viObject->centerPos.y - TOPLEFT_Y)/TILESIZE)*TILESIZE;
				_viObject->rc.left = _viObject->centerPos.x - TILESIZE / 2;
				_viObject->rc.right = _viObject->centerPos.x + TILESIZE / 2;
				_viObject->rc.top = _viObject->centerPos.y - TILESIZE / 2;
				_viObject->rc.bottom = _viObject->centerPos.y + TILESIZE / 2;
			}
			_viObject->select = false;
		}
	}

}

void TileObject::render(void) {
	for (_viObject = _vObject.begin(); _viObject != _vObject.end(); ++_viObject) {
		_viObject->image->render(getMemDC(), _viObject->rc.left, _viObject->rc.top);
	}
}
