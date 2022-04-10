#include "Stdafx.h"
#include "MainGame.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "ShopScene.h"
#include "ClearScene.h"
#include "MinigameScene.h"

HRESULT MainGame::init(void) {
	GameNode::init(true);
	initSound();
	SCENEMANAGER->addScene("Title", new TitleScene);
	SCENEMANAGER->addScene("Game", new GameScene);
	SCENEMANAGER->addScene("Shop", new ShopScene);
	SCENEMANAGER->addScene("Clear", new ClearScene);
	SCENEMANAGER->addScene("Minigame", new MinigameScene);

	SCENEMANAGER->changeScene("Title");

	return S_OK;
}

void MainGame::release(void) {
	GameNode::release();

}

void MainGame::update(void) {
	GameNode::update();
	SCENEMANAGER->update();
}

void MainGame::render() {
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
	//=============================================
	SCENEMANAGER->render();
	OBSERVERMANAGER->render();
	//=============================================
	TIMEMANAGER->render(getMemDC());
	this->getBackBuffer()->render(getHDC());
}

void MainGame::initSound(void) {
	SOUNDMANAGER->addSound("Title", "Resources/Sounds/bgm/02. Crazy Dave (Intro Theme).mp3", true, true);
	SOUNDMANAGER->addSound("Setting", "Resources/Sounds/bgm/Choose.mp3", true, true);
	SOUNDMANAGER->addSound("Stage1", "Resources/Sounds/bgm/04. Grasswalk.mp3", true, true);
	SOUNDMANAGER->addSound("Minigame", "Resources/Sounds/bgm/05. Loonboon.mp3", true, true);
	SOUNDMANAGER->addSound("Stage2", "Resources/Sounds/bgm/06. Moongrains.mp3", true, true);
	SOUNDMANAGER->addSound("Reward", "Resources/Sounds/bgm/07. Zen Garden.mp3", true, true);
	SOUNDMANAGER->addSound("Stage3", "Resources/Sounds/bgm/08. Watery Graves (slow).mp3", true, true);

	SOUNDMANAGER->addSound("ReadySetPlant", "Resources/Sounds/sfx/readysetplant.mp3", false, false);
	SOUNDMANAGER->addSound("SelectPlant", "Resources/Sounds/sfx/SelectPlant.mp3", false, false);
	SOUNDMANAGER->addSound("Plant", "Resources/Sounds/sfx/Plant.mp3", false, false);
	SOUNDMANAGER->addSound("Peashooter", "Resources/Sounds/sfx/Peashooter.mp3", false, false);
	SOUNDMANAGER->addSound("Puff", "Resources/Sounds/sfx/Puff.mp3", false, false);
	SOUNDMANAGER->addSound("Hit", "Resources/Sounds/sfx/hit1.mp3", false, false);
	SOUNDMANAGER->addSound("Explode", "Resources/Sounds/sfx/explode.mp3", false, false);
	SOUNDMANAGER->addSound("Sun", "Resources/Sounds/sfx/Sun.mp3", false, false);
}
