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
		_inventory가 _deck의 MAX치보다 같거나 적을 경우
		or Ready 버튼을 누를 경우
		*/
		/*
		선행작업
		1. 인벤토리 랜더링 중지
		2. 카메라 돌리기
		*/
		_status = GameStatus::PLAY;
	}break;
	case GameStatus::PLAY: {
		//Ready, Set, Plant! 화면 선행
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
	//	파일 받아서 로드
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
			//Deck 클릭시 PLANT로 넘어감
		} break;
		case CursorSelect::PLANT: {
			//투명 식물 이미지가 마우스를 따라옴
			//마우스+타일일 경우 

			//타일 클릭시
				//식물이 없다면 식물 설치
			//NONE으로 넘어감
		} break;
		case CursorSelect::SHOVEL: {
			//타일 클릭시
				//식물이 있다면 식물 제거
			//NONE으로 넘어감
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
