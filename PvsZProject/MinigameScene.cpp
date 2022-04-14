#include "Stdafx.h"
#include "MinigameScene.h"

HRESULT MinigameScene::init(void) {
	//init Image & Class
	_background = IMAGEMANAGER->addImage("Stage1", "Resources/Images/Backgrounds/Stage1.bmp", 894, 384, false, RGB(255, 0, 255));
	_blackChanger = IMAGEMANAGER->addImage("blackChanger", "Resources/Images/Backgrounds/BlackSceneChanger.bmp", 548, 384, false, RGB(255, 0, 255));
	_selectedPlantIcon = IMAGEMANAGER->addFrameImage("PlantIcon", "Resources/Images/Objects/PlantIcon.bmp", 1900, 80, 25, 1, true, RGB(255, 0, 255));
	_readyLetter = IMAGEMANAGER->addFrameImage("ReadyLetter", "Resources/Images/Objects/ReadySetPlant.bmp", 1176, 141, 3, 1, true, RGB(255, 0, 255));
	_waveLetter = IMAGEMANAGER->addImage("WaveLetter", "Resources/Images/Objects/WaveText.bmp", 548, 23, true, RGB(255, 0, 255));

	//init Variable
	_status = MinigameStatus::READY;
	_cursor = MinigameCursorSelect::NONE;
	_blackAlpha = 255;
	_goingClear = false;

	//init Camera Variable
	_camera = RectMake(0, 0, WINSIZE_X, WINSIZE_Y);	
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

	//init Variable
	_zombieCount = TIMEMANAGER->getWorldTime();
	_zombieCooltime = 10.0f;

	_beltCount = TIMEMANAGER->getWorldTime();
	_beltCooltime = 7.0f;

	_selectedPlant = PlantType::NONE;
	_selectedPlantIndex = -1;

	_clickReward = false;
	_clickRewardCount = 7.0f;

	//init Class
	_tile = new Tile;
	_tile->init(0);

	vector<int> _zombieType;
	_zombieType.push_back(0);
	_zombieType.push_back(1);
	_zombieType.push_back(2);
	_zl = new ZombieList;
	_zl->init(_zombieType, &_camera);

	_zm = new ZombieManager;
	_zm->init();
	_zm->setStage(0);

	_bm = new BulletManager;
	_bm->init();
	_bm->setStage(0);

	_belt = new Belt;
	_belt->init();

	_pm = new PlantManager;
	_pm->init();
	_pm->setTileMemory(_tile);
	_pm->setStage(0);

	_reward = new Reward;
	_reward->init(4);

	return S_OK;
}

void MinigameScene::release(void) {
}

void MinigameScene::update(void) {
	OBSERVERMANAGER->update();


	if (_status == MinigameStatus::READY) updateReady();
	else if (_status == MinigameStatus::PLAY) updatePlay();
}

void MinigameScene::render(void) {
	_background->render(getMemDC(), 0, 0, _camera.left, _camera.top, 548, 384);
	if (_blackAlpha > 0) _blackChanger->alphaRender(getMemDC(), _blackAlpha);
	if (_status == MinigameStatus::READY) printReady();
	else if (_status == MinigameStatus::PLAY) printPlay();
	_selectedPlantIcon->frameRender(getMemDC(), _ptMouse.x - _selectedPlantIcon->getFrameWidth() / 2, _ptMouse.y - _selectedPlantIcon->getFrameHeight() / 2, static_cast<int>(_selectedPlant), 0);
}

void MinigameScene::updateReady() {
	sceneControl();
	if(_readyTextShow) updateReadyText();
}

void MinigameScene::sceneControl() {
	sceneChangerControl();
	cameraControl();
}

void MinigameScene::sceneChangerControl() {
	if (_goingClear && _blackAlpha >= 253) {
		_pm->release();
		_zm->release();
		_bm->release();
		stopAllSound();

		SCENEMANAGER->changeScene("Clear");
	}
	if (_blackAlpha > 0) {
		(_goingClear) ? _blackAlpha += 2 : _blackAlpha -= 2;
		if (_blackAlpha > 255) _blackAlpha = 255;
		else if (_blackAlpha < 0) _blackAlpha = 0;
	}

	if (_clickReward && _clickRewardTime + _clickRewardCount < TIMEMANAGER->getWorldTime()) {
		_goingClear = true;
	}
}

void MinigameScene::cameraControl() {
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
			_cameraLeft = true;
			_cameraCount = TIMEMANAGER->getWorldTime();
			_cameraMoveSpeed = 0.0f;
		}
	}


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

void MinigameScene::updateReadyText() {
	if (_readyTime + _readyCount < TIMEMANAGER->getWorldTime()) {
		if (_readyFrame != 2) {
			_readyTime = TIMEMANAGER->getWorldTime();
			_readyFrame++;
		}
		else if (_readyFrame == 2) {
			stopAllSound();
			SOUNDMANAGER->play("Minigame", 1.0f);

			_status = MinigameStatus::PLAY;
			_progressbar = new Progressbar;
			_stageTimer = 180.0f;
			_stageWaveTimer.push_back(90.0f);
			_stageWaveTimer.push_back(179.9f);
			_progressbar->init(_stageTimer, _stageWaveTimer);

			_zombieCount = TIMEMANAGER->getWorldTime();
			_beltCount = TIMEMANAGER->getWorldTime();
		}
	}
}



void MinigameScene::updatePlay() {
	_progressbar->update();
	zombieControl();
	mouseControl();
	beltControl();

	_pm->update();
	_zm->update();
	_bm->update();
	_belt->update();
	_tile->update();
	if (_reward->isShow()) _reward->update();
}

void MinigameScene::mouseControl() {
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		switch (_cursor) {
			case MinigameCursorSelect::NONE: {

				if (PtInRect(&_reward->getRect(), _ptMouse) && _reward->isShow() && _reward->getStatus() == RewardStatus::GENERATE) {
					_reward->setObtain();
					_clickReward = true;
					_clickRewardTime = TIMEMANAGER->getWorldTime();
				}

				_selectedPlantIndex = _belt->selectCard();
				if (_selectedPlantIndex != -1 && _belt->getCard(_selectedPlantIndex)->isActive()) {
					_selectedPlant = _belt->getPlant(_selectedPlantIndex);
					_cursor = MinigameCursorSelect::PLANT;
					SOUNDMANAGER->play("SelectPlant", 1.0f);
					break;
				}
			} break;
			case MinigameCursorSelect::PLANT: {
				int tempIndex = _tile->selectTile();
				if (tempIndex != -1 && _selectedPlant != PlantType::NONE) {
					_tile->setPlant(tempIndex, false);
					_pm->addPlant(_belt->getPlant(_selectedPlantIndex), _tile->getLocation(tempIndex));
					_belt->removeCard(_selectedPlantIndex);

					_cursor = MinigameCursorSelect::NONE;
					_selectedPlant = PlantType::NONE;
					_selectedPlantIndex = -1;
					SOUNDMANAGER->play("Plant", 1.0f);
				}
			} break;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) {
		switch (_cursor) {
			case MinigameCursorSelect::PLANT: {
				_cursor = MinigameCursorSelect::NONE;
				_selectedPlant = PlantType::NONE;
				_selectedPlantIndex = -1;
			} break;
		}
	}
}

void MinigameScene::zombieControl() {
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
			ZombieType tempType = static_cast<ZombieType>(RND->getInt(3));
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
			ZombieType tempType = static_cast<ZombieType>(RND->getInt(3));
			_zm->addZombie(tempType, i);
		}
	}

	_waveTextShow = _progressbar->isAnounceTime();
}

void MinigameScene::beltControl() {
	if (_belt->getSize() >= 9) return;
	static int _wallnutBowlingCount = 0;
	if (_beltCount + _beltCooltime < TIMEMANAGER->getWorldTime()) {
		if (_wallnutBowlingCount > 6) {
			int rndTemp = RND->getFromIntTo(1, 3);
			if (rndTemp == 1) _belt->addCard(PlantType::EXPLODEBOWLING);
			else  _belt->addCard(PlantType::WALLNUTBOWLING);
		}
		else _belt->addCard(PlantType::WALLNUTBOWLING);
		_wallnutBowlingCount++;
		_beltCount = TIMEMANAGER->getWorldTime();
	}
}

void MinigameScene::printReady() {
	if (_status == MinigameStatus::READY) {
		_zl->render();
		if (_readyTextShow) _readyLetter->frameRender(getMemDC(), 100, 120, _readyFrame, 0);
	}
}

void MinigameScene::printPlay() {
	if (_progressbar) _progressbar->render();
	_belt->render();
	_tile->render();
	_pm->render();
	_zm->render();
	_bm->render();
	if (_reward->isShow()) _reward->render();
}

void MinigameScene::stopAllSound() {
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
