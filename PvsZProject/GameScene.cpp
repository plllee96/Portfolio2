#include "Stdafx.h"
#include "GameScene.h"

HRESULT GameScene::init(void) {
	_camera = RectMake(100, 0, WINSIZE_X, WINSIZE_Y);		//tempCameraPosition
	_background = IMAGEMANAGER->addImage("Background", "Resources/Images/Backgrounds/Stage1.bmp", 894, 384, false, RGB(255, 0, 255));
	_status = GameStatus::SETTING;
	_cursor = CursorSelect::NONE;
	_selectedPlant = PlantType::NONE;
	_selectedPlantIndex = -1;
	_sunCount = TIMEMANAGER->getWorldTime();

	////////////////////////////////
	//loadStage();
	_stageNum = 0;
	///////////////////////////////

	_sun = 50;
	_sun = 50000;			//debug
	_sunCooltime = 10.0f;
	_tile = new Tile;
	_tile->init(_stageNum);

	//init Class
	_pm = new PlantManager;
	_pm->init();

	_deck = new Deck;
	_deck->init();

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
	_background->render(getMemDC(), 0, 0, _camera.left, _camera.top, 548, 384);

	//debug
	_tile->render();

	//render Object
	for (Sun* iter : _vSun) {
		iter->render();
	}

	//render UI
	if(_cursor == CursorSelect::NONE) _deck->render();
	else _deck->disableRender();

	if (_cursor == CursorSelect::PLANT) {
		printSelectedPlant();
	}

	char str[256];
	wsprintf(str, "%d", _sun);
	TextOut(getMemDC(), 50, 10, str, strlen(str));

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

	_pm->update();
	_deck->update();
	_tile->update();
}

void GameScene::mouseControl() {
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		switch (_cursor) {
		case CursorSelect::NONE: {
			//Click Sun
			_viSun = _vSun.begin();
			for (; _viSun != _vSun.end(); ++_viSun) {
				if (PtInRect(&(*_viSun)->getRect(), _ptMouse)) {
					_sun += 25;
					(*_viSun)->setType(SunType::GAIN);
					break;
				}
			}

			//Select PlantCard from Deck
			_selectedPlantIndex = _deck->selectCard();
			if (_selectedPlantIndex != -1 && _deck->getCard(_selectedPlantIndex)->isActive() && _deck->getCard(_selectedPlantIndex)->getPrice() <= _sun) {
				_selectedPlant = _deck->getPlant(_selectedPlantIndex);
				_cursor = CursorSelect::PLANT;
			}

			//Select Shovel

		} break;
		case CursorSelect::PLANT: {
			int tempIndex = _tile->selectTile();
			if (tempIndex != -1 && _selectedPlant != PlantType::NONE) {
				if (!_tile->getTile(tempIndex).hasPlant) {
					//_pm�� _selectedPlant �߰�
					_tile->setPlant(tempIndex, true);
					_pm->addPlant(_deck->getPlant(_selectedPlantIndex), _tile->getLocation(tempIndex));
					_deck->getCard(_selectedPlantIndex)->startCoolTime();
					_sun -= _deck->getCard(_selectedPlantIndex)->getPrice();
				}
			}
			_cursor = CursorSelect::NONE;
			_selectedPlant = PlantType::NONE;
			_selectedPlantIndex = -1;
		} break;
		case CursorSelect::SHOVEL: {
			int tempIndex = _tile->selectTile();
			if (tempIndex != -1 && _selectedPlant != PlantType::NONE) {
				if (_tile->getTile(tempIndex).hasPlant) {
					//_pm�� _selectedPlant ����
					_tile->setPlant(tempIndex, false);
				}
			}
			_cursor = CursorSelect::NONE;
		} break;
		}

	}
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) {
		switch (_cursor) {
		case CursorSelect::PLANT: {
			_cursor = CursorSelect::NONE;
			_selectedPlant = PlantType::NONE;
			_selectedPlantIndex = -1;
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

//===============================================================
// Render
//===============================================================
void GameScene::printSelectedPlant() {
	switch (_selectedPlant) {
		//���Ŀ� plant render�� �ٲ� ��
		case PlantType::PEASHOOTER: break;
		case PlantType::SUNFLOWER: break;
		case PlantType::WALLNUT: break;
		case PlantType::CHERRYBOMB: break;
		default: break;
	}
}


//===============================================================
// Debug
//===============================================================
string GameScene::printPlantType(PlantType type) {
	switch (type) {
		case PlantType::NONE: return "NONE";
		case PlantType::PEASHOOTER: return "�ǽ���";
		case PlantType::SUNFLOWER: return "���ö��";
		case PlantType::WALLNUT: return "����";
		case PlantType::CHERRYBOMB: return "ü����ź";
		default: return "";
	}
}
