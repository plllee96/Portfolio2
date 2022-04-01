#include "Stdafx.h"
#include "ZombieList.h"

HRESULT ZombieList::init(vector<int> list, RECT* camera) {
	_zombieListCount = TIMEMANAGER->getWorldTime();
	for (int i = 0; i < list.size(); i++) {
		tagZombieList tempList;
		tempList.type = static_cast<ZombieType>(list[i]);
		tempList.frameX = RND->getInt(4);
		tempList.x = RND->getFromIntTo(720, 820);
		tempList.y = i * (300 / list.size()) + 40;
		switch (tempList.type) {
			case ZombieType::ZOMBIE: {
				tempList.image = IMAGEMANAGER->IMAGEMANAGER->addFrameImage("NormalZombie", "Resources/Images/Zombies/Zombie.bmp", 910, 700, 13, 7, true, RGB(255, 0, 255));
			} break;
			case ZombieType::CORNHEAD_ZOMBIE: {
				tempList.image = IMAGEMANAGER->addFrameImage("CornheadZombie", "Resources/Images/Zombies/CornheadZombie.bmp", 490, 550, 7, 5, true, RGB(255, 0, 255));
			} break;
			case ZombieType::BUCKETHEAD_ZOMBIE: {
				tempList.image = IMAGEMANAGER->addFrameImage("BucketheadZombie", "Resources/Images/Zombies/BucketheadZombie.bmp", 476, 530, 7, 5, true, RGB(255, 0, 255));
			} break;
			default: {
				tempList.image = IMAGEMANAGER->addFrameImage("NormalZombie", "Resources/Images/Zombies/Zombie.bmp", 910, 700, 13, 7, true, RGB(255, 0, 255));
			} break;
		}
		_list.push_back(tempList);
	}
	_camera = camera;
	return S_OK;
}

void ZombieList::release(void) {
}

void ZombieList::update(void) {
	if (_zombieListCount + zombieListCool < TIMEMANAGER->getWorldTime()) {
		for (int i = 0; i < _list.size(); i++) {
			_list[i].frameX += 1;
			if (_list[i].frameX > 3) _list[i].frameX = 0;
		}
		_zombieListCount = TIMEMANAGER->getWorldTime();
	}
}

void ZombieList::render(void) {
	for (tagZombieList iter : _list) {
		iter.image->frameRender(getMemDC(), iter.x - (*_camera).left, iter.y - (*_camera).top, iter.frameX, 0);
	}
}
