#include "Stdafx.h"
#include "GameScene.h"

HRESULT GameScene::init(void) {
	_camera = RectMake(0, 0, WINSIZE_X, WINSIZE_Y);		//tempCameraPosition
	_sunIcon = IMAGEMANAGER->addImage("SunIcon", "Resources/Images/Objects/SunIcon.bmp", 32, 32, true, RGB(255, 0, 255));
	_playGameButton = IMAGEMANAGER->addImage("Playbutton", "Resources/Images/Objects/playButton.bmp", 75, 47, true, RGB(255,0,255));
	_status = GameStatus::SETTING;
	_cursor = CursorSelect::NONE;
	_selectedPlant = PlantType::NONE; 
	_selectedPlantIndex = -1;

	_inventory = new Inventory;
	_inventory->init();

	_deck = new Deck;
	_deck->init();

	////////////////////////////////
	loadStage();

	switch (_stageNum) {
		case 0: _background = IMAGEMANAGER->addImage("Stage1", "Resources/Images/Backgrounds/Stage1.bmp", 894, 384, false, RGB(255, 0, 255)); break;
		case 1: _background = IMAGEMANAGER->addImage("Stage2", "Resources/Images/Backgrounds/Stage2.bmp", 894, 384, false, RGB(255, 0, 255)); break;
		case 2: _background = IMAGEMANAGER->addImage("Stage3", "Resources/Images/Backgrounds/Stage3.bmp", 894, 384, false, RGB(255, 0, 255)); break;
		case 3: break;
		default : _background = IMAGEMANAGER->addImage("Stage1", "Resources/Images/Backgrounds/Stage1.bmp", 894, 384, false, RGB(255, 0, 255));
	}

	//init Game Variable
	_startbuttonRc = RectMake(460, 220, _playGameButton->getWidth(), _playGameButton->getHeight());

	_sun = 5000;
	_sunCount = TIMEMANAGER->getWorldTime();
	if (_stageNum == 0 || _stageNum == 2) _sunCooltime = 7.0f;
	else _sunCooltime = 9999.0f;
	_sunNumX = 78;
	_sunNumY = 30;

	_zombieCount = TIMEMANAGER->getWorldTime();
	_zombieCooltime = 10.0f;

	//init Camera Variable
	_cameraCount = TIMEMANAGER->getWorldTime();
	_cameraMoveSpeed = 0.0f;
	_cameraMoveRightDelay = 2.0f;
	_cameraMoveLeftDelay = 1.0f;
	_cameraRight = true;
	_cameraLeft = false;

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

	return S_OK;
}

void GameScene::release(void) {
}

void GameScene::update(void) {
	switch (_status) {
	case GameStatus::SETTING: {
		moveCamera();
		settingGame();
	}break;
	case GameStatus::PLAY: {
		//Ready, Set, Plant! 화면 선행
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

	//render Object
	if (_status == GameStatus::PLAY) {
		_tile->render();
		_pm->render();
		_zm->render();
		_bm->render();
	}

	//render UI
	if (_status == GameStatus::PLAY) {
		_sunIcon->render(getMemDC(), 70, 0);
		_sunNum->render(_sun);
	}


	if (_progressbar) _progressbar->render();
	for (Sun* iter : _vSun) {
		iter->render();
	}

	if(_status == GameStatus::SETTING && !_cameraRight && !_cameraLeft) _inventory->render();
	if(_cursor == CursorSelect::NONE && !_cameraRight) _deck->render(_sun);
	else _deck->disableRender();

	if (_status == GameStatus::SETTING && !(_cameraLeft || _cameraRight)) {
		_playGameButton->render(getMemDC(), _startbuttonRc.left, _startbuttonRc.top);
	}

	if (_cursor == CursorSelect::PLANT) {
		printSelectedPlant();
	}
}

void GameScene::moveCamera() {
	if (_cameraRight) {
		if (_cameraMoveSpeed > 2.0f) _cameraMoveSpeed = 2.0f;
		else _cameraMoveSpeed += 0.05f;

		if (_cameraMoveRightDelay + _cameraCount < TIMEMANAGER->getWorldTime()) {
			_camera.left += _cameraMoveSpeed;
			_camera.right += _cameraMoveSpeed;
		}

		if (_camera.left >= 350) {
			_camera.left = 350;
			_camera.right = 350 + WINSIZE_X;
			_cameraRight = false;
			_cameraMoveSpeed = 0.0f;
		}
	}

	//Active only Start Game (Setting -> Play)
	if (_cameraLeft) {
		if (_cameraMoveSpeed > 2.0f) _cameraMoveSpeed = 2.0f;
		else _cameraMoveSpeed += 0.05f;

		if (_cameraMoveLeftDelay + _cameraCount < TIMEMANAGER->getWorldTime()) {
			_camera.left -= _cameraMoveSpeed;
			_camera.right -= _cameraMoveSpeed;
		}

		if (_camera.left <= 100) {
			_camera.left = 100;
			_camera.right = 100 + WINSIZE_X;
			_cameraLeft = false;

			
			_status = GameStatus::PLAY;
			_sunCount = TIMEMANAGER->getWorldTime();
			_zombieCount = TIMEMANAGER->getWorldTime();
		}
	}
}



//===============================================================
// Set, Load
//===============================================================
void GameScene::loadStage() {
	//	이후 파일에서 데이터를 받아서 로드하는 것으로 바꿀 것
	_stageNum = 2;

	_maxSlot = 6;
	_deck->setMaxSlot(6);
	
	for (int i = 1; i < 16; i++) {
		_inventory->addCard(static_cast<PlantType>(i));
	}

	_stageTimer = 180.0f;
	_stageWaveTimer.push_back(90.0f);
	_stageWaveTimer.push_back(179.9f);
}

void GameScene::settingGame() {
	settingMouseControl();
	_inventory->update();
}

void GameScene::settingMouseControl() {
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		//Click Inventory to Add Card
		int selectedIndex = _inventory->selectCard();
		if (selectedIndex != -1 && _inventory->getCard(selectedIndex)->isActive() &&
			_deck->getCurrentSlot() < _maxSlot) {
			_deck->addCard(
				_inventory->getCard(selectedIndex)->getPlantType(),
				_inventory->getPrice(_inventory->getCard(selectedIndex)->getPlantType()),
				_inventory->getCooltime(_inventory->getCard(selectedIndex)->getPlantType())
			);
			_inventory->activeCard(selectedIndex, false);
		}

		//Click Deck to Remove Card
		int selectedDeckIndex = _deck->selectCard();
		if (selectedDeckIndex != -1) {
			_inventory->activeCard(_inventory->getIndex(_deck->getCard(selectedDeckIndex)->getPlantType()), true);
			_deck->removeCard(selectedDeckIndex);
		}

		if (PtInRect(&_startbuttonRc, _ptMouse) && _deck->getCurrentSlot() == _maxSlot) {
			_cameraLeft = true;
		}
	}


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
						
						else if (_tile->getTile(tempIndex).hasLilypad) {	//Lilypad가 설치되어 있는 타일인 경우에만 설치
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
					//_pm에 _selectedPlant 제거
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
	float _runningTime = TIMEMANAGER->getWorldTime() - _progressbar->getStartTime();
	

	if (_progressbar->isEndWave()) {
		if (_zm->getZombieAmount() == 0) {
			cout << "클리어" << endl;
		}
		return;
	}
	if (_runningTime < 15.0f) return;

	else if (_runningTime >= 15.0f && _runningTime < 45.0f) {
		if (_zombieCount + _zombieCooltime < TIMEMANAGER->getWorldTime()) {
			_zombieCount = TIMEMANAGER->getWorldTime();
			//_zm->addZombie(ZombieType::ZOMBIE, RND->getInt(_tile->getRow()));
			_zm->addZombie(ZombieType::CORNHEAD_ZOMBIE, 1);
		}
	}
	else {
		if (_zombieCount + _zombieCooltime < TIMEMANAGER->getWorldTime()) {
			_zombieCount = TIMEMANAGER->getWorldTime();
			_zm->addZombie(ZombieType::ZOMBIE, RND->getInt(_tile->getRow()));	//이후 ZombieType부분 무작위로 수정
		}
	}
	if (_runningTime >= 30.0f) {
		_zombieCooltime -= 0.001f;
		if (_zombieCooltime < 7.0f) _zombieCooltime = 7.0f;
	}

	if (_progressbar->isHugeWaveTime()) {
		for (int i = 0; i < _tile->getRow(); i++) {
			_zm->addZombie(ZombieType::ZOMBIE, i);
		}
	}
}

//===============================================================
// Render
//===============================================================
void GameScene::printSelectedPlant() {
	switch (_selectedPlant) {
		//이후에 plant render로 바꿀 것
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
		case PlantType::PEASHOOTER: return "피슈터";
		case PlantType::SUNFLOWER: return "선플라워";
		case PlantType::WALLNUT: return "월넛";
		case PlantType::CHERRYBOMB: return "체리폭탄";
		default: return "";
	}
}
