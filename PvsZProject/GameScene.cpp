#include "Stdafx.h"
#include "GameScene.h"

HRESULT GameScene::init(void) {
	
	//Init UI Image
	_camera = RectMake(0, 0, WINSIZE_X, WINSIZE_Y);		//tempCameraPosition
	_sunIcon = IMAGEMANAGER->addImage("SunIcon", "Resources/Images/Objects/SunIcon.bmp", 32, 32, true, RGB(255, 0, 255));
	_playGameButton = IMAGEMANAGER->addImage("Playbutton", "Resources/Images/Objects/playButton.bmp", 75, 47, true, RGB(255,0,255));
	_shopButton = IMAGEMANAGER->addImage("Shopbutton", "Resources/Images/Objects/shopButton.bmp", 75, 49, true, RGB(255, 0, 255));
	_selectedPlantIcon = IMAGEMANAGER->addFrameImage("PlantIcon", "Resources/Images/Objects/PlantIcon.bmp", 1292, 80, 17, 1, true, RGB(255, 0, 255));
	_readyLetter = IMAGEMANAGER->addFrameImage("ReadyLetter", "Resources/Images/Objects/ReadySetPlant.bmp", 1176, 141, 3, 1, true, RGB(255, 0, 255));
	_waveLetter = IMAGEMANAGER->addImage("WaveLetter", "Resources/Images/Objects/WaveText.bmp", 548, 23, true, RGB(255, 0, 255));
	
	
	//Init SceneChanger
	_whiteChanger = IMAGEMANAGER->addImage("whiteChanger", "Resources/Images/Backgrounds/WhiteSceneChanger.bmp", 548, 384, false, RGB(255, 0, 255));
	_blackChanger = IMAGEMANAGER->addImage("blackChanger", "Resources/Images/Backgrounds/BlackSceneChanger.bmp", 548, 384, false, RGB(255, 0, 255));
	_whiteAlpha = 0;
	_blackAlpha = 255;
	_goingToClear = false;
	_goingToShop = false;


	if (_progressbar) {
		_progressbar->clearProgressbar();
		_progressbar = nullptr;
		delete _progressbar;
	}
	_status = GameStatus::SETTING;
	_cursor = CursorSelect::NONE;
	_selectedPlant = PlantType::NONE; 
	_selectedPlantIndex = -1;

	_zombieType.clear();
	_stageWaveTimer.clear();

	_inventory = new Inventory;
	_inventory->init();

	_deck = new Deck;
	_deck->init();

	// ==============================================
	loadStage();
	// ==============================================
	// ! Add in-Game data after loadStage() Function


	switch (_stageNum) {
		case 0: _background = IMAGEMANAGER->addImage("Stage1", "Resources/Images/Backgrounds/Stage1.bmp", 894, 384, false, RGB(255, 0, 255)); break;
		case 1: _background = IMAGEMANAGER->addImage("Stage2", "Resources/Images/Backgrounds/Stage2.bmp", 894, 384, false, RGB(255, 0, 255)); break;
		case 2: _background = IMAGEMANAGER->addImage("Stage3", "Resources/Images/Backgrounds/Stage3.bmp", 894, 384, false, RGB(255, 0, 255)); break;
		case 3: break;
		default : _background = IMAGEMANAGER->addImage("Stage1", "Resources/Images/Backgrounds/Stage1.bmp", 894, 384, false, RGB(255, 0, 255));
	}

	//init Game Variable
	_startbuttonRc = RectMake(460, 220, _playGameButton->getWidth(), _playGameButton->getHeight());
	_shopbuttonRc = RectMake(460, 165, _shopButton->getWidth(), _shopButton->getHeight());

	_vSun.clear();
	_sun = 100;
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

	//init Event Variable
	_readyTextShow = false;
	_readyCount = 0.6f;
	_readyFrame = 0;

	_waveTextShow = false;

	_clickReward = false;
	_clickRewardCount = 7.0f;

	//init Class
	_tile = new Tile;
	_tile->init(_stageNum);

	_sunNum = new NumberImage;
	_sunNum->init(&_sunNumX, &_sunNumY);

	_zl = new ZombieList;
	_zl->init(_zombieType, &_camera);

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

	_reward = new Reward;
	_reward->init(_stageNum);

	SOUNDMANAGER->play("Setting", 1.0f);

	return S_OK;
}

void GameScene::release(void) {
}

void GameScene::update(void) {
	sceneChangerControl();

	switch (_status) {
	case GameStatus::SETTING: {
		_zl->update();
		moveCamera();
		settingGame();
		if (_readyTextShow) updateReadyText();
	}break;
	case GameStatus::PLAY: {
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
	//render Background
	_background->render(getMemDC(), 0, 0, _camera.left, _camera.top, 548, 384);

	//render Object
	if (_status == GameStatus::SETTING) {
		_zl->render();
		if (_readyTextShow) _readyLetter->frameRender(getMemDC(), 100, 120, _readyFrame, 0);
	}
	if (_status == GameStatus::PLAY) {
		_tile->render();
		_pm->render();
		_zm->render();
		_bm->render();
	}
	
	if (_reward->isShow()) _reward->render();

	//render UI
	if (_status == GameStatus::PLAY) {
		_sunIcon->render(getMemDC(), 70, 0);
		_sunNum->render(_sun);
	}

	if (_progressbar && _status == GameStatus::PLAY) _progressbar->render();
	for (Sun* iter : _vSun) {
		iter->render();
	}

	if(_status == GameStatus::SETTING && !_cameraRight && !_cameraLeft && !_readyTextShow) _inventory->render();
	if(_cursor == CursorSelect::NONE && !_cameraRight) _deck->render(_sun);
	else _deck->disableRender();

	if (_status == GameStatus::SETTING && !(_cameraLeft || _cameraRight) && !_readyTextShow) {
		_playGameButton->render(getMemDC(), _startbuttonRc.left, _startbuttonRc.top);
		_shopButton->render(getMemDC(), _shopbuttonRc.left, _shopbuttonRc.top);
	}

	if (_cursor == CursorSelect::PLANT) {
		printSelectedPlant();
	}

	if (_status == GameStatus::PLAY && _waveTextShow) {
		_waveLetter->render(getMemDC(), 0, 190);
	}

	//render ScreenImage
	if (_whiteAlpha > 0) _whiteChanger->alphaRender(getMemDC(), _whiteAlpha);
	if (_blackAlpha > 0) _blackChanger->alphaRender(getMemDC(), _blackAlpha);

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

			_readyTextShow = true;
			SOUNDMANAGER->play("ReadySetPlant", 1.0f);
			_readyTime = TIMEMANAGER->getWorldTime();

		}
	}
}

void GameScene::sceneChangerControl() {
	if (!_goingToClear && !_goingToShop) _blackAlpha -= 2;
	if (_blackAlpha < 0) _blackAlpha = 0;

	if (_goingToShop) {
		if (_blackAlpha > 253) {
			_pm->release();
			_zm->release();
			_bm->release();
			stopAllSound();
			SCENEMANAGER->changeScene("Shop");
		}
		else _blackAlpha += 2;
	}

	if (_goingToClear) {
		if (_whiteAlpha > 253) {
			//pm, zm, bm ÃÊ±âÈ­
			_pm->release();
			_zm->release();
			_bm->release();
			stopAllSound();
			
			SCENEMANAGER->changeScene("Clear");
		}
		else _whiteAlpha += 2;
	}

	if (_clickReward && _clickRewardTime + _clickRewardCount < TIMEMANAGER->getWorldTime()) {
		_goingToClear = true;
	}
}



//===============================================================
// Set, Load
//===============================================================
void GameScene::loadStage() {
	vector<string> vData = TEXTDATAMANAGER->load("data.txt");

	_stageNum = atoi(vData[0].c_str());

	_maxSlot = atoi(vData[1].c_str());
	_deck->setMaxSlot(_maxSlot);
	
	for (int i = 3; i < vData.size(); i++) {
		int tempPlantNum = atoi(vData[i].c_str());
		_inventory->addCard(static_cast<PlantType>(tempPlantNum));
	}


	switch (_stageNum) {
		case 0: {
			_stageTimer = 120.0f;
			_stageWaveTimer.push_back(119.9f);

			//_stageTimer = 40.0f;
			//_stageWaveTimer.push_back(39.9f);

			_zombieType.push_back(0);
			_zombieType.push_back(1);
		} break;
		case 1: {
			_stageTimer = 120.0f;
			_stageWaveTimer.push_back(119.9f);

			//_stageTimer = 45.0f;
			//_stageWaveTimer.push_back(44.9f);

			_zombieType.push_back(0);
			_zombieType.push_back(1);
			_zombieType.push_back(2);
		} break;
		case 2: {
			_stageTimer = 180.0f;
			_stageWaveTimer.push_back(90.0f);
			_stageWaveTimer.push_back(179.9f);

			_zombieType.push_back(0);
			_zombieType.push_back(1);
			_zombieType.push_back(2);
			_zombieType.push_back(5);
		} break;
		default: {
			_stageTimer = 120.0f;
			_stageWaveTimer.push_back(119.9f);

			_zombieType.push_back(0);
			_zombieType.push_back(1);
		} break;
	}

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

		//Click Start Button to Play Game
		if (PtInRect(&_startbuttonRc, _ptMouse) && _deck->getCurrentSlot() == _maxSlot) {
			_cameraLeft = true;
		}

		//Click Shop Button to move Shop
		if (PtInRect(&_shopbuttonRc, _ptMouse)) {
			_goingToShop = true;
		}
	}


}

void GameScene::updateReadyText() {
	if (_readyTime + _readyCount < TIMEMANAGER->getWorldTime()) {
		if (_readyFrame != 2) {
			_readyTime = TIMEMANAGER->getWorldTime();
			_readyFrame++;
		}
		else if (_readyFrame == 2) {
			stopAllSound();
			switch (_stageNum) {
				case 0: SOUNDMANAGER->play("Stage1", 1.0f); break;
				case 1: SOUNDMANAGER->play("Stage2", 1.0f); break;
				case 2: SOUNDMANAGER->play("Stage3", 1.0f); break;
			}
			_status = GameStatus::PLAY;
			_progressbar = new Progressbar;
			_progressbar->init(_stageTimer, _stageWaveTimer);

			_sunCount = TIMEMANAGER->getWorldTime();
			_zombieCount = TIMEMANAGER->getWorldTime();
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

	if (_reward->isShow()) _reward->update();

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
				SOUNDMANAGER->play("SelectPlant", 1.0f);
				break;
			}

			//Click Sun
			_viSun = _vSun.begin();
			for (; _viSun != _vSun.end(); ++_viSun) {
				if (PtInRect(&(*_viSun)->getRect(), _ptMouse)) {
					((*_viSun)->isSmall()) ? _sun += 15 : _sun += 25;
					(*_viSun)->setType(SunType::GAIN);
					SOUNDMANAGER->play("Sun", 1.0f);
					break;
				}
			}

			//Select Reward
			if (PtInRect(&_reward->getRect(), _ptMouse) && _reward->isShow() && _reward->getStatus() == RewardStatus::GENERATE) {
				_reward->setObtain();
				_clickReward = true;
				_clickRewardTime = TIMEMANAGER->getWorldTime();
			}

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
							SOUNDMANAGER->play("Plant", 1.0f);
						}
					}
					else if (_tile->getTile(tempIndex).isWater) {
						if (_selectedPlant == PlantType::LILYPAD) {
							_tile->setPlant(tempIndex, false);
							_tile->setLilypad(tempIndex, true);
							_pm->addPlant(_deck->getPlant(_selectedPlantIndex), _tile->getLocation(tempIndex));
							_deck->getCard(_selectedPlantIndex)->startCoolTime();
							_sun -= _deck->getCard(_selectedPlantIndex)->getPrice();
							SOUNDMANAGER->play("Plant", 1.0f);
						}
						
						else if (_tile->getTile(tempIndex).hasLilypad) {	
							_tile->setPlant(tempIndex, true);
							_pm->addPlant(_deck->getPlant(_selectedPlantIndex), _tile->getLocation(tempIndex));
							_deck->getCard(_selectedPlantIndex)->startCoolTime();
							_sun -= _deck->getCard(_selectedPlantIndex)->getPrice();
							SOUNDMANAGER->play("Plant", 1.0f);
						}
					}
					else {
						if (_selectedPlant != PlantType::GRAVEBUSTER && _selectedPlant != PlantType::LILYPAD) {
							_tile->setPlant(tempIndex, true);
							_pm->addPlant(_deck->getPlant(_selectedPlantIndex), _tile->getLocation(tempIndex));
							_deck->getCard(_selectedPlantIndex)->startCoolTime();
							_sun -= _deck->getCard(_selectedPlantIndex)->getPrice();
							SOUNDMANAGER->play("Plant", 1.0f);
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
			_reward->spawnReward(true, _zm->getLastZombiePosition().x, _zm->getLastZombiePosition().y);
		}
		return;
	}
	if (_runningTime < 15.0f) return;

	else if (_runningTime >= 15.0f && _runningTime < 45.0f) {
		if (_zombieCount + _zombieCooltime < TIMEMANAGER->getWorldTime()) {
			_zombieCount = TIMEMANAGER->getWorldTime();
			_zm->addZombie(ZombieType::ZOMBIE, RND->getInt(_tile->getRow()));
		}
	}
	else {
		if (_zombieCount + _zombieCooltime < TIMEMANAGER->getWorldTime()) {
			ZombieType tempType = static_cast<ZombieType>(_zombieType[RND->getInt(_zombieType.size())]);
			_zombieCount = TIMEMANAGER->getWorldTime();
			_zm->addZombie(tempType, RND->getInt(_tile->getRow()));
		}
	}
	if (_runningTime >= 30.0f) {
		_zombieCooltime -= 0.001f;
		if (_zombieCooltime < 7.0f) _zombieCooltime = 7.0f;
	}

	if (_progressbar->isHugeWaveTime()) {
		for (int i = 0; i < _tile->getRow(); i++) {
			ZombieType tempType = static_cast<ZombieType>(_zombieType[RND->getInt(_zombieType.size())]);
			_zm->addZombie(tempType, i);
		}
	}

	_waveTextShow = _progressbar->isAnounceTime();
}

//===============================================================
// Render
//===============================================================
void GameScene::printSelectedPlant() {
	_selectedPlantIcon->frameRender(getMemDC(), _ptMouse.x - _selectedPlantIcon->getFrameWidth()/2, _ptMouse.y - _selectedPlantIcon->getFrameHeight() / 2, static_cast<int>(_selectedPlant), 0);
}


//===============================================================
// Debug
//===============================================================
string GameScene::printPlantType(PlantType type) {
	switch (type) {
		case PlantType::NONE: return "NONE";
		case PlantType::PEASHOOTER: return "ÇÇ½´ÅÍ";
		case PlantType::SUNFLOWER: return "¼±ÇÃ¶ó¿ö";
		case PlantType::WALLNUT: return "¿ù³Ó";
		case PlantType::CHERRYBOMB: return "Ã¼¸®ÆøÅº";
		default: return "";
	}
}

void GameScene::stopAllSound() {
	SOUNDMANAGER->stop("Title");
	SOUNDMANAGER->stop("Setting");
	SOUNDMANAGER->stop("Stage1");
	SOUNDMANAGER->stop("Minigame");
	SOUNDMANAGER->stop("Stage2");
	SOUNDMANAGER->stop("Reward");
	SOUNDMANAGER->stop("Stage3");
	SOUNDMANAGER->stop("ReadySetPlant");
	SOUNDMANAGER->stop("SelectPlant");
	SOUNDMANAGER->stop("Plant");
	SOUNDMANAGER->stop("Peashooter");
	SOUNDMANAGER->stop("Puff");
	SOUNDMANAGER->stop("Hit");
	SOUNDMANAGER->stop("Explode");
	SOUNDMANAGER->stop("Sun");
}
