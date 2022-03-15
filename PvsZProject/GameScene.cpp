#include "Stdafx.h"
#include "GameScene.h"

HRESULT GameScene::init(void) {
	_camera = RectMake(100, 0, WINSIZE_X, WINSIZE_Y);		//tempCameraPosition
	_background = IMAGEMANAGER->addImage("Background", "Resources/Images/Backgrounds/Stage1.bmp", 894, 384, false, RGB(255, 0, 255));
	_status = GameStatus::SETTING;
	_cursor = CursorSelect::NONE;

	_sunCount = TIMEMANAGER->getWorldTime();

	//loadStage();
	_sun = 50;
	_sunCooltime = 10.0f;
	return S_OK;
}

void GameScene::release(void) {
}

void GameScene::update(void) {
	switch (_status) {
	case GameStatus::SETTING: {
		/*
		_inventory�� _deck�� MAXġ���� ���ų� ���� ���
		or Ready ��ư�� ���� ���
		*/
		/*
		�����۾�
		1. �κ��丮 ������ ����
		2. ī�޶� ������
		*/
		_status = GameStatus::PLAY;
	}break;
	case GameStatus::PLAY: {
		//Ready, Set, Plant! ȭ�� ����
		playGame();
	}break;
	case GameStatus::PAUSE: {

	}break;
	case GameStatus::CLEAR: {

	}break;
	}
}

//===============================================================
// Set, Load
//===============================================================
void GameScene::render(void) {
	//cout << _ptMouse.x << "," << _ptMouse.y << endl;
	cout << _sun << endl;
	_background->render(getMemDC(), 0, 0, _camera.left, _camera.top, 548, 384);

	for (Sun* iter : _vSun) {
		iter->render();
	}
}

void GameScene::loadStage() {
	//	���� �޾Ƽ� �ε�
}

//===============================================================
// Play Game
//===============================================================
void GameScene::playGame() {
	mouseControl();
	sunControl();

}

void GameScene::mouseControl() {
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		switch (_cursor) {
		case CursorSelect::NONE: {
			_viSun = _vSun.begin();
			for (; _viSun != _vSun.end(); ++_viSun) {
				if (PtInRect(&(*_viSun)->getRect(), _ptMouse)) {
					_sun += 25;
					(*_viSun)->setType(SunType::GAIN);
					break;
				}
			}
			//Deck Ŭ���� PLANT�� �Ѿ
		} break;
		case CursorSelect::PLANT: {
			//���� �Ĺ� �̹����� ���콺�� �����
			//���콺+Ÿ���� ��� 

			//Ÿ�� Ŭ����
				//�Ĺ��� ���ٸ� �Ĺ� ��ġ
			//NONE���� �Ѿ
		} break;
		case CursorSelect::SHOVEL: {
			//Ÿ�� Ŭ����
				//�Ĺ��� �ִٸ� �Ĺ� ����
			//NONE���� �Ѿ
		} break;
		}

	}
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) {
		switch (_cursor) {
		case CursorSelect::PLANT: {
			_cursor = CursorSelect::NONE;
		} break;
		case CursorSelect::SHOVEL: {
			_cursor = CursorSelect::NONE;
		} break;
		}
	}
}

void GameScene::sunControl() {
	if (_sunCount + _sunCooltime < TIMEMANAGER->getWorldTime()) {
		_sunCount = TIMEMANAGER->getWorldTime();
		Sun* sun = new Sun;
		sun->init(SunType::FALL);
		_vSun.push_back(sun);
	}
	_viSun = _vSun.begin();
	for (; _viSun != _vSun.end();) {
		(*_viSun)->update();
		if ((*_viSun)->isOverTime() || (*_viSun)->isCompleteObtained()) {
			(*_viSun)->release();
			_vSun.erase(_viSun);
			break;
		}
		else _viSun++;
	}


}
