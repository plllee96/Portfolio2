#include "Stdafx.h"
#include "TitleScene.h"

HRESULT TitleScene::init(void) {
	_image = IMAGEMANAGER->addImage("Title", "Resources/Images/Backgrounds/Title.bmp", 548, 821, false, RGB(255, 0, 255));
	_buttonImage = IMAGEMANAGER->addImage("TitleButton", "Resources/Images/Objects/TitleButton.bmp", 220, 236, true, RGB(255, 0, 255));
	_sceneChanger = IMAGEMANAGER->addImage("blackChanger", "Resources/Images/Backgrounds/BlackSceneChanger.bmp", 548, 384, false, RGB(255, 0, 255));
	_sceneAlpha = 0;
	_sceneChange = false;
	_goingMinigame = false;

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

	_nameLength = MAX_LENGTH;
	_userName[MAX_LENGTH] = { 0, };
	INT nError = GetUserName(_userName, &_nameLength);

	_userNameImage = new LetterImage;
	_userNameImage->init(_nameLength, _userName);

	_buttonPosition = { 280, 460 };
	
	return S_OK;
}

void TitleScene::release(void) {
}

void TitleScene::update(void) {
	if (_camera.bottom > 0 && _waitCount + 4.0f < TIMEMANAGER->getWorldTime()) {
		_camera.top -= 1;
		_camera.bottom -= 1;
	}

	RECT temp = RectMake(_camera.left + _buttonPosition.x, _camera.top + _buttonPosition.y, _buttonImage->getWidth(), _buttonImage->getHeight() / 3);
	RECT temp2 = RectMake(_camera.left + _buttonPosition.x, _camera.top + _buttonPosition.y + _buttonImage->getHeight() / 3 * 2, _buttonImage->getWidth(), _buttonImage->getHeight() / 3);
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		if (PtInRect(&temp, _ptMouse)) {
			_sceneChange = true;
		}
		else if (PtInRect(&temp2, _ptMouse)) {
			_goingMinigame = true;
			_sceneChange = true;
		}
	}

	if (_sceneChange) _sceneAlpha += 4;
	if (_sceneAlpha > 250) {
		if (_goingMinigame) SCENEMANAGER->changeScene("Minigame");
		else SCENEMANAGER->changeScene("Game");
	}
}

void TitleScene::render(void) {
	_image->render(getMemDC(), _camera.left, _camera.top);
	_buttonImage->render(getMemDC(), _camera.left + _buttonPosition.x, _camera.top + _buttonPosition.y);

	_userNameImage->render(_camera.left + 70, _camera.top + 465);

	if (_sceneAlpha != 0) _sceneChanger->alphaRender(getMemDC(), _sceneAlpha);
}

void TitleScene::initFirstData() {
	_firstData.stage = 0;
//	_firstData.stage = 2;
	_firstData.slot = 6;
	_firstData.money = 0;
	for (int i = 1; i <= 6; i++) {
		_firstData.inventory.push_back(i);
	}

	//debug
	for (int i = 7; i <= 16; i++) {
		_firstData.inventory.push_back(i);
	}
}
