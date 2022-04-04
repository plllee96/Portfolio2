#include "Stdafx.h"
#include "TitleScene.h"

HRESULT TitleScene::init(void) {
	_image = IMAGEMANAGER->addImage("Title", "Resources/Images/Backgrounds/Title.bmp", 548, 821, false, RGB(255, 0, 255));
	_camera = RectMake(0, 0, WINSIZE_X, WINSIZE_Y);
	_waitCount = TIMEMANAGER->getWorldTime();
	initFirstData();

	char temp[32];
	vector<string> data;
	data.push_back(_itoa((int)_firstData.stage, temp, 10));
	data.push_back(_itoa((int)_firstData.slot, temp, 10));
	data.push_back(_itoa((int)_firstData.money, temp, 10));
	for (int i = 0; i < _firstData.inventory.size(); i++) {
		data.push_back(_itoa((int)_firstData.inventory[i], temp, 10));
	}
	TEXTDATAMANAGER->save("data.txt", data);
	
	return S_OK;
}

void TitleScene::release(void) {
}

void TitleScene::update(void) {
	if (_camera.bottom > 0 && _waitCount + 4.0f < TIMEMANAGER->getWorldTime()) {
		_camera.top -= 1;
		_camera.bottom -= 1;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) {
		SCENEMANAGER->changeScene("Game");
	}
}

void TitleScene::render(void) {
	_image->render(getMemDC(), _camera.left, _camera.top);
}

void TitleScene::initFirstData() {
	_firstData.stage = 0;
	_firstData.slot = 6;
	_firstData.money = 1000;
	for (int i = 1; i <= 6; i++) {
		_firstData.inventory.push_back(i);
	}
}
