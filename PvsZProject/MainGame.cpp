#include "Stdafx.h"
#include "MainGame.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "ShopScene.h"
#include "ClearScene.h"

HRESULT MainGame::init(void) {
	GameNode::init(true);
	SCENEMANAGER->addScene("Title", new TitleScene);
	SCENEMANAGER->addScene("Game", new GameScene);
	SCENEMANAGER->addScene("Shop", new ShopScene);
	SCENEMANAGER->addScene("Clear", new ClearScene);


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

	//=============================================
	TIMEMANAGER->render(getMemDC());
	this->getBackBuffer()->render(getHDC());
}
