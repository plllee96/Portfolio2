#include "Stdafx.h"
#include "ClearScene.h"

HRESULT ClearScene::init(void) {
	_whiteChanger = IMAGEMANAGER->addImage("whiteChanger", "Resources/Images/Backgrounds/WhiteSceneChanger.bmp", 548, 384, false, RGB(255, 0, 255));
	_blackChanger = IMAGEMANAGER->addImage("blackChanger", "Resources/Images/Backgrounds/BlackSceneChanger.bmp", 548, 384, false, RGB(255, 0, 255));

	_goingMain = false;
	_goingNextStage = false;
	_whiteAlpha = 254;
	_blackAlpha = 0;

	_nextStageRc = RectMake(40, 330, 215, 50);
	_mainRc = RectMake(285, 330, 215, 50);

	_vData = TEXTDATAMANAGER->load("data.txt");
	_stageNum = atoi(_vData[0].c_str());
	_money = atoi(_vData[2].c_str());

	switch (_stageNum) {
		case 0: _background = IMAGEMANAGER->addImage("Reward0", "Resources/Images/Backgrounds/reward_0.bmp", 548, 384, false, RGB(255, 0, 255)); break;
		case 1: _background = IMAGEMANAGER->addImage("Reward1", "Resources/Images/Backgrounds/reward_1.bmp", 548, 384, false, RGB(255, 0, 255)); break;
		case 2: _background = IMAGEMANAGER->addImage("Reward1", "Resources/Images/Backgrounds/reward_1.bmp", 548, 384, false, RGB(255, 0, 255)); break;
	}

	SOUNDMANAGER->play("Reward", 1.0f);

	addReward();

	return S_OK;
}

void ClearScene::release(void) {
}

void ClearScene::update(void) {
	sceneChanger();
	mouseControl();
}

void ClearScene::render(void) {
	_background->render(getMemDC());
	
	if (_whiteAlpha > 0) _whiteChanger->alphaRender(getMemDC(), _whiteAlpha);
	if (_blackAlpha > 0) _blackChanger->alphaRender(getMemDC(), _blackAlpha);
}

void ClearScene::addReward() {
	char temp[32];

	switch (_stageNum) {
		case 0: {
			_vData.push_back(_itoa((int)7, temp, 10));
			_vData.push_back(_itoa((int)8, temp, 10));
			_vData.push_back(_itoa((int)9, temp, 10));
			_vData.push_back(_itoa((int)10, temp, 10));
			_vData.push_back(_itoa((int)11, temp, 10));
		} break;
		case 1: {
			_vData.push_back(_itoa((int)12, temp, 10));
			_vData.push_back(_itoa((int)13, temp, 10));
			_vData.push_back(_itoa((int)14, temp, 10));
			_vData.push_back(_itoa((int)15, temp, 10));
		} break;
		case 2: break;
	}
	TEXTDATAMANAGER->save("data.txt", _vData);
}

void ClearScene::sceneChanger() {
	if (_whiteAlpha > 0) _whiteAlpha-= 2;

	if (_goingMain || _goingNextStage) _blackAlpha += 2;
	if (_blackAlpha > 254) {
		SOUNDMANAGER->stop("Reward");
		if (_goingMain) SCENEMANAGER->changeScene("Title");
		if (_goingNextStage) SCENEMANAGER->changeScene("Game");
	}
}

void ClearScene::mouseControl() {
	if (_goingMain || _goingNextStage) return;

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		if (PtInRect(&_mainRc, _ptMouse)) {
			_goingMain = true;
		}
		
		if (PtInRect(&_nextStageRc, _ptMouse)) {
			char temp[32];
			_vData[0] = _itoa((int)_stageNum + 1, temp, 10);
			_vData[2] = _itoa((int)_money + 500, temp, 10);
			TEXTDATAMANAGER->save("data.txt", _vData);

			_goingNextStage = true;
		}
	}
}
