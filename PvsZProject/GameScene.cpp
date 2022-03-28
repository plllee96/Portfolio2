#include "Stdafx.h"
#include "GameScene.h"

HRESULT GameScene::init(void) {
	_camera = RectMake(100, 0, WINSIZE_X, WINSIZE_Y);		//tempCameraPosition
	_sunIcon = IMAGEMANAGER->addImage("SunIcon", "Resources/Images/Objects/SunIcon.bmp", 32, 32, true, RGB(255, 0, 255));

	_status = GameStatus::PLAY;
	_cursor = CursorSelect::NONE;
	_selectedPlant = PlantType::NONE; 
	_selectedPlantIndex = -1;

	////////////////////////////////
	//loadStage();
	_stageNum = 2;
	switch (_stageNum) {
		case 0: _background = IMAGEMANAGER->addImage("Stage1", "Resources/Images/Backgrounds/Stage1.bmp", 894, 384, false, RGB(255, 0, 255)); break;
		case 1: _background = IMAGEMANAGER->addImage("Stage2", "Resources/Images/Backgrounds/Stage2.bmp", 894, 384, false, RGB(255, 0, 255)); break;
		case 2: _background = IMAGEMANAGER->addImage("Stage3", "Resources/Images/Backgrounds/Stage3.bmp", 894, 384, false, RGB(255, 0, 255)); break;
		case 3: break;
		default : _background = IMAGEMANAGER->addImage("Stage1", "Resources/Images/Backgrounds/Stage1.bmp", 894, 384, false, RGB(255, 0, 255));
	}
	
	//debug
	_stageTimer = 180.0f;
	_stageWaveTimer.push_back(90.0f);
	_stageWaveTimer.push_back(179.9f);
	///////////////////////////////

	_sun = 1000;
	_sunCount = TIMEMANAGER->getWorldTime();
	if (_stageNum == 0 || _stageNum == 2) _sunCooltime = 7.0f;
	else _sunCooltime = 9999.0f;
	_sunNumX = 78;
	_sunNumY = 30;

	_zombieCount = TIMEMANAGER->getWorldTime();
	_zombieCooltime = 10.0f;

	//init Class
	_tile = new Tile;
	_tile->init(_stageNum);

	_sunNum = new NumberImage;
	_sunNum->init(&_sunNumX, &_sunNumY);

	_zm = new ZombieManager;
	_zm->init();
	_zm->setStage(_stageNum);

	_bm = new BulletManager;
	_bm->init();
	_bm->setStage(_stageNum);

	_pm = new PlantManager;
	_pm->init();
	_pm->setTileMemory(_tile);
	_pm->setStage(_stageNum);

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
		Ready ��ư�� ������ ��� && (Deck�� maxDeck ������ ���� ���
			1. �κ��丮 ������ ����
			2. ī�޶� �̵�(if ������ġ�� �ƴ� : �̵�, ������ġ�� ���� : GameStatus::PLAY
			//_status = GameStatus::PLAY;
		*/
	}break;
	case GameStatus::PLAY: {
		//Ready, Set, Plant! ȭ�� ����
		if (!_progressbar) {
			_progressbar = new Progressbar;
			_progressbar->init(_stageTimer, _stageWaveTimer);
		}
		else _progressbar->update();

		playGame();
	}break;
	case GameStatus::PAUSE: {

	}break;
	case GameStatus::CLEAR: {

	}break;
	}
}

void GameScene::render(void) {
	//cout << _ptMouse.x << "," << _ptMouse.y << endl;
	_background->render(getMemDC(), 0, 0, _camera.left, _camera.top, 548, 384);

	//debug
	_tile->render();

	//render Object
	_pm->render();
	_zm->render();
	_bm->render();

	//render UI
	_sunIcon->render(getMemDC(), 70, 0);
	_sunNum->render(_sun);

	if (_progressbar) _progressbar->render();
	for (Sun* iter : _vSun) {
		iter->render();
	}

	if(_cursor == CursorSelect::NONE) _deck->render(_sun);
	else _deck->disableRender();

	if (_cursor == CursorSelect::PLANT) {
		printSelectedPlant();
	}
}

//===============================================================
// Set, Load
//===============================================================
void GameScene::loadStage() {
	//	���� �޾Ƽ� �ε�
}

//===============================================================
// Play Game
//===============================================================
void GameScene::playGame() {
	OBSERVERMANAGER->update();
	mouseControl();
	sunControl();
	zombieControl();

	_pm->update();
	_zm->update();
	_bm->update();

	_deck->update();
	_tile->update();
	_sunNum->update();
}

void GameScene::mouseControl() {
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		switch (_cursor) {
		case CursorSelect::NONE: {
			//Select PlantCard from Deck
			_selectedPlantIndex = _deck->selectCard();
			if (_selectedPlantIndex != -1 && _deck->getCard(_selectedPlantIndex)->isActive() && _deck->getCard(_selectedPlantIndex)->getPrice() <= _sun) {
				_selectedPlant = _deck->getPlant(_selectedPlantIndex);
				_cursor = CursorSelect::PLANT;
				break;
			}

			//Click Sun
			_viSun = _vSun.begin();
			for (; _viSun != _vSun.end(); ++_viSun) {
				if (PtInRect(&(*_viSun)->getRect(), _ptMouse)) {
					((*_viSun)->isSmall()) ? _sun += 15 : _sun += 25;
					(*_viSun)->setType(SunType::GAIN);
					break;
				}
			}

			//Select Shovel

		} break;
		case CursorSelect::PLANT: {
			int tempIndex = _tile->selectTile();
			if (tempIndex != -1 && _selectedPlant != PlantType::NONE) {
				if (!_tile->getTile(tempIndex).hasPlant) {
					if (_tile->getTile(tempIndex).hasObstacle) {
						if (_selectedPlant == PlantType::GRAVEBUSTER) {
							_tile->setPlant(tempIndex, true);
							_pm->addPlant(_deck->getPlant(_selectedPlantIndex), _tile->getLocation(tempIndex));
							_deck->getCard(_selectedPlantIndex)->startCoolTime();
							_sun -= _deck->getCard(_selectedPlantIndex)->getPrice();
						}
					}
					else if (_tile->getTile(tempIndex).isWater) {
						if (_selectedPlant == PlantType::LILYPAD) {
							_tile->setPlant(tempIndex, false);
							_tile->setLilypad(tempIndex, true);
							_pm->addPlant(_deck->getPlant(_selectedPlantIndex), _tile->getLocation(tempIndex));
							_deck->getCard(_selectedPlantIndex)->startCoolTime();
							_sun -= _deck->getCard(_selectedPlantIndex)->getPrice();
						}
						
						else if (_tile->getTile(tempIndex).hasLilypad) {	//Lilypad�� ��ġ�Ǿ� �ִ� Ÿ���� ��쿡�� ��ġ
							_tile->setPlant(tempIndex, true);
							_pm->addPlant(_deck->getPlant(_selectedPlantIndex), _tile->getLocation(tempIndex));
							_deck->getCard(_selectedPlantIndex)->startCoolTime();
							_sun -= _deck->getCard(_selectedPlantIndex)->getPrice();
						}
					}
					else {
						if (_selectedPlant != PlantType::GRAVEBUSTER && _selectedPlant != PlantType::LILYPAD) {
							_tile->setPlant(tempIndex, true);
							_pm->addPlant(_deck->getPlant(_selectedPlantIndex), _tile->getLocation(tempIndex));
							_deck->getCard(_selectedPlantIndex)->startCoolTime();
							_sun -= _deck->getCard(_selectedPlantIndex)->getPrice();
						}
					}
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
	generateTypeContainer temp = _pm->isGeneratePlant();
	if (temp.isGenerate) {
		Sun* sun = new Sun;
		sun->init(SunType::GENERATE, temp.x, temp.y);
		if (temp.isSmallSun) sun->setSmall();
		_vSun.push_back(sun);

		if (temp.isTwin) {
			Sun* sun2 = new Sun;
			sun2->init(SunType::GENERATE, temp.x, temp.y);
			if (temp.isSmallSun) sun2->setSmall();
			_vSun.push_back(sun2);
		}
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

void GameScene::zombieControl() {
	//wave�ð��� �� ��� 8�� �� �뷮 ����

	if (_zombieCount + _zombieCooltime < TIMEMANAGER->getWorldTime()) {
		_zombieCount = TIMEMANAGER->getWorldTime();
		_zm->addZombie(ZombieType::ZOMBIE, RND->getInt(_tile->getRow()));
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
