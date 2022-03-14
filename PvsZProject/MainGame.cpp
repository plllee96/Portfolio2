#include "Stdafx.h"
#include "MainGame.h"
#include "StartScene.h"

HRESULT MainGame::init(void) {
	GameNode::init(true);
	SCENEMANAGER->addScene("Start", new StartScene);

	SCENEMANAGER->changeScene("Start");

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
